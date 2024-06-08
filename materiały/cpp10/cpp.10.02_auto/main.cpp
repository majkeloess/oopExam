#include <iostream>
#include <cmath>
#include <typeinfo>

template <class T, class U>
auto add(T t, U u) -> decltype(t + u) // c++11 needs return type
// auto add(T t, U u) // works ok in c++14
{
    return t + u;
}

int main()
{
    auto a = 1 + 2;
    std::cout << "type of a: " << typeid(a) << '\n';

    auto b = add(1, 1.2);
    std::cout << "type of b: " << typeid(b) << '\n';

    auto d = {1, 2};
    std::cout << "type of d: " << typeid(d) << '\n';
}
