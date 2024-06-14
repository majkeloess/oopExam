#include <iostream>
#include <list>
#include <algorithm>

// jak chce tak rozwiązać to musze  pamiętać że iterator potem do lambdy to jest const int
auto f1 = [](const int &a)
{ return 1; };
auto f2 = [](const int &a) -> bool
{ return a % 2 == 0; };

struct f3
{
    int m_value{};
    f3(int value) : m_value{value} {}
    void operator()(int &i)
    {
        i += m_value;
    }
};

template <typename Iter, typename Function>
void print_to_if(std::ostream &out, Iter iterbeg, Iter iterend, Function f)
{
    // WERSJA I
    for (Iter i = iterbeg; i != iterend; i++)
    {
        if (f(*i))
        {
            std::cout << *i << " ";
        }
    }
    std::cout << std::endl;
}

template <typename Iter, typename Function>
void change(Iter iterbeg, Iter iterend, Function f)
{
    std::for_each(iterbeg, iterend, f);
}

int main()
{
    const auto cl = {1, 2, 3, 4, 5, 6, 7};

    print_to_if(std::cout << "All: ", begin(cl), end(cl), f1);
    print_to_if(std::cout << "All: ", begin(cl), end(cl), f2);

    int add_value{-1};
    std::list<int> cl2 = {7, 6, 5, 4, 3, 2, 1};
    change(begin(cl2), end(cl2), f3{add_value});
    print_to_if(std::cout << "All  ", begin(cl2), end(cl2), f1);
}
/*
All: 1 2 3 4 5 6 7
All: 2 4 6
All  6 5 4 3 2 1 0
*/