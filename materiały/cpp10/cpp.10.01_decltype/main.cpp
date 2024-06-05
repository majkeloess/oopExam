#include <iostream>
#include <typeinfo>
#include "../type.hpp"

struct A { double x = 0; };
 
int main() 
{
    int i = 33;
    decltype(i) j = i * 2;

    const A* a = new A;

    decltype(a->x) x3 = 1;        // type of x3 is double (declared type)
    decltype((a->x)) x4 = x3; // type of x4 is const double& (lvalue expression)

    x3 = 5;
    // x4 = 5; // cannot assign to variable 'x4' with const-qualified type 'decltype((a->x))'

    std::cout << "i (" << type(i) << ") = " << i << ", "
              << "j (" << type(j) << ") = " << j << ", "
              << "x3 (" << type(x3) << ") = " << x3 << ", "
              << "x4 (" << type(x4) << ") = " << x4 << "\n";

 
}