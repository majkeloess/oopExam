#include <iostream>

template<typename T>
struct B;

template<typename T>
struct B
{
    using value_type = T;
    B(T val): _v(val) {}
    value_type get() const {return _v;}
private:
    value_type _v = value_type();
};

template<typename T>
struct B<T*>
{
    using value_type = T;
    B(T* ptr) : _p(ptr){}
    B(const B<T*>&) = delete;
    B<T*>& operator=(const B<T*>&) = delete;
    value_type get() const {return *_p;}
private:
    value_type* _p;
};

int main()
{
    typedef B<int> int_b;
    typedef B<int*> int_p_b;        //jednak typedef

    int_b a(1);
    int_b a_copy(a);
    int_p_b b(new int_p_b::value_type{2});
    // int_p_b e = b; //error
    // b=b //error
    
    std::cout << "a=" << a.get() << std::endl;
    std::cout << "a_copy=" << a_copy.get()+1 << std::endl;
    std::cout <<" b=" << b.get()+1 << std::endl;
}
/*
a=1
a_copy=2
 b=3
*/