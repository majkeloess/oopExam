#include <iostream>

struct A
{
    A() = default;
    int i{};
};

template <typename T>
struct ptr
{
    T *m_ptr{};
    ptr() = default;
    explicit ptr(T *ptr) : m_ptr{ptr} {}
    ptr(const ptr &other) = delete;
    ptr &operator=(const ptr &other) = delete;

    T &operator*()
    {
        return *m_ptr;
    }

    T *operator->()
    {
        return m_ptr;
    }

    const T &operator*() const
    {
        return *m_ptr;
    }

    const T *operator->() const
    {
        return m_ptr;
    }

    friend bool operator==(const ptr &p1, const ptr &p2)
    {
        return p1.m_ptr == p2.m_ptr;
    }
    friend bool operator!=(const ptr &p1, const ptr &p2)
    {
        return p1.m_ptr != p2.m_ptr;
    }
};

int main()
{
    const ptr<A> a(new A);
    const ptr<A> b;
    ptr<A> c(new A);

    // ptr<A>  _b_error = new A;      // Odkomentowanie powoduje błąd kompilacji
    // a = a;               // Odkomentowanie powoduje błąd kompilacji
    // const ptr<A> _c_error = a;     // Odkomentowanie powoduje błąd kompilacji

    std::cout << (((*a).i, a->i)) << " " << ++c->i << " ";
    std::cout << (a == ptr<A>()) << " " << (a != b) << "\n";
}