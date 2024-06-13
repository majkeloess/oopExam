#include <utility>
#include <iostream>


template<typename T = float>
struct Type_t
{
    Type_t() = default;
    Type_t(T x) : _v(x){}
    friend std::ostream & operator<<(std::ostream & os,const Type_t& t)
    {
        return os<<t._v;
    }
    T _v;
};
template<typename T>
struct ptr
{
    ptr() = default;
    using value_type = T;
    ptr(const ptr& o) = delete;
    ptr& operator=(const ptr& o) = delete;
    ptr& operator=(ptr&& o) = delete;
    explicit ptr(T* obj) : _p(obj) {}
    ptr(ptr&& o)
    {
        _p = o._p;
        o._p = nullptr;
    }

    T& operator*() const
    {
        return *_p;
    }
    T* operator->() const
    {
        return _p;
    }
        
    private:
    T* _p;

};

using Float_t = Type_t<>;

int main()
{
    using Type_t = ptr<std::pair<Float_t, Float_t>>; //

    Type_t t1{new Type_t::value_type{}};
    // Type_t t2 = t1;
    // Type_t t2; t2 = t1;
    // Type_t t2 = new Type_t::value_type();
    // Powyższe się mają nie kompilować
    (*t1).first = Type_t::value_type::first_type{1.};
    t1->second = Type_t::value_type::second_type{2.5};

    Type_t t2 = std::move(t1);

    // t3=std::move(t2); 
    const Type_t t3{new Type_t::value_type{}};                                 
    //(*t3).first= 13;
    // t3->second = 13;
    // Powyższe się mają nie kompilować
    (*t3).first = Type_t::value_type::first_type{1};  
    t3->second = Type_t::value_type::second_type{2.5};

    
    std::cout << (*t3).first._v << ", " << t3->second << std::endl;
}
/* output:
1, 2.5
*/