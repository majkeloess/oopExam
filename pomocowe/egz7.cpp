#include <iostream>

template <typename T>
class B;

template <typename T>
class B
{
private:
    T m_val{};

public:
    using value_type = T;

    explicit B(T val) : m_val{val} {}

    T get() const
    {
        return m_val;
    }
};

// Ta część definiuje specjalizację szablonu klasy B dla przypadku, gdy parametr T jest wskaźnikiem(T *).Oznacza to, że ta klasa będzie działać inaczej niż ogólna klasa B<T> dla typów innych niż wskaźniki.

// Celem tej specjalizacji jest zapewnienie, że obiekty B<T *> będą zawsze przechowywać unikalne wskaźniki i nie będzie można ich kopiować ani przypisywać do innych obiektów.Jest to typowe podejście, gdy chcemy kontrolować czas życia obiektu wskazywanego przez wskaźnik.W tym przypadku, odpowiedzialność za zwolnienie pamięci należy do właściciela obiektu B<T *>

template <typename T>
class B<T *>
{
public:
    T *m_val{};

public:
    using value_type = T;

    B(T *val) : m_val{val} {}
    B(const B<T *> &) = delete;
    B<T *> &operator=(const B<T *> &) = delete;
    T get() const
    {
        return *m_val;
    }
};

int main()
{
    typedef B<int> int_b;
    typedef B<int *> int_p_b; // jednak typedef

    int_b a(1);
    int_b a_copy(a);
    int_p_b b(new int_p_b::value_type{2});
    // int_p_b e = b; // error
    // b = b;         // error

    std::cout
        << "a=" << a.get() << std::endl;
    std::cout << "a_copy=" << a_copy.get() + 1 << std::endl;
    std::cout << " b=" << b.get() + 1 << std::endl;
}
/*
a=1
a_copy=2
b=3
*/