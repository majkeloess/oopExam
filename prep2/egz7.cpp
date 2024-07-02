#include <iostream>


template <typename T>
struct B{
    T m_val{};
    B(T val) : m_val{val} {}

    T get() const 
    {
        return m_val;
    }
};

template <typename T>
struct B<T*>{
    using value_type = T;
    T *m_ptr{};
    B(T *ptr) : m_ptr{ptr} {}
    B(const B &other) = delete;
    B &operator=(const B &other) = delete;


    T get() const 
    {
        return *m_ptr;
    }

    ~B()
    {
        delete m_ptr;
    }

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