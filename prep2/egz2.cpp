#include <iostream>
#include <utility>

template <typename T = float>
struct Type_t
{
    T _v{};
    Type_t() = default;
    explicit Type_t(T val) : _v{val} {}

    friend std::ostream &operator<<(std::ostream &out, const Type_t &t)
    {
        out << t._v;
        return out;
    }
};

template <typename T>
struct ptr
{
    using value_type = T;
    T *m_ptr{};
    ptr() = default;
    explicit ptr(T *ptr) : m_ptr{ptr} {}
    ptr(const ptr &other) = delete;
    ptr(ptr &&other) noexcept : m_ptr{other.m_ptr}
    {
        other.m_ptr = nullptr;
    }
    ptr &operator=(const ptr &other) = delete;
    ptr &operator=(ptr &&other) noexcept
    {
        if (this != &other)
        {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T &operator*() const
    {
        return *m_ptr;
    }

    T *operator->() const
    {
        return m_ptr;
    }

    ~ptr()
    {
        delete m_ptr;
        m_ptr = nullptr;
    }
};

int main()
{
    using Float_t = Type_t<>;
    using Test_t = ptr<std::pair<Float_t, Float_t>>;

    Test_t t1{new Test_t::value_type{}};
    // Test_t t2 = t1;                            // BLAD KOMPILACJI
    // Test_t t3; t3 = t1;                        // BLAD KOMPILACJI
    // Test_t t4 = new Test_t::value_type();    // BLAD KOMPILACJI

    (*t1).first = Test_t::value_type::first_type{1};
    t1->second = Test_t::value_type::second_type{3.141};

    Test_t t2;
    t2 = std::move(t1);
    std::cout << (*t2).first << ", " << t2->second._v << "\n";

    const Test_t t3 = std::move(t2);
    // (*t3).first = 13;       //  BLAD KOMPILACJI
    // t3->second = 13;        //  BLAD KOMPILACJI

    std::cout << (*t3).first._v << ", " << t3->second << "\n";

    return 0;
}
/* output:
1, 3.141
1, 3.141
*/