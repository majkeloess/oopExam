#include <iostream>
#include <array>
#include <string>
#include <memory>

void my_print_el(std::string prefix)
{
    std::cout << prefix;
}

using arr_uniq_2 = std::array<std::unique_ptr<int>, 2>;
using uniq_int = std::unique_ptr<int>;

void my_print(arr_uniq_2 &arr, std::string a, std::string b)
{
    std::cout << "[";
    for (auto &el : arr)
    {
        std::cout << *el << a;
    }
    std::cout << "] " << b << " ";
}

void my_print(arr_uniq_2 &arr)
{
    std::cout << "[";
    for (auto &el : arr)
    {
        std::cout << *el << ";";
    }
    std::cout << "] " << "\n ";
}

void my_swap(uniq_int &a, uniq_int &b)
{
    std::swap(a, b);
}

void my_swap(int &a, int &b)
{
    std::swap(a, b);
}

// nienawidze cpp, jak kurwa pisac na kartce aaaaaaaaaaaa
int main()
{
    std::array<std::unique_ptr<int>, 2> a = {
        std::unique_ptr<int>(new int{1}),
        std::unique_ptr<int>(new int{2})};

    my_print_el("----------------\n");
    my_print(a, ";", " -> ");
    my_swap(a[0], a[1]);
    my_print(a, ";", " -> ");
    my_swap(*a[0], *a[1]);
    my_print(a);
    my_print_el("----------------");
}
//[1;2;] -> [2;1;] -> [1;2;]