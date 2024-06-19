#include <iostream>
#include <utility>

int main()
{
    std::cout << "a->";
    A a;
    std::cout << "b->";
    A b(1);
    std::cout << "c->";
    A c(1, 2);

    std::cout << "d->";
    A d = std::move(c);

    // A e = c;
    // A f = 1;
}
/*
a-> A::A(int,int): _a=0,_b=0
A::A(): _a=0,_b=0
b-> A::A(int,int): _a=1,_b=0
A::A(int): _a=1,_b=0
c-> A::A(int,int): _a=1,_b=2
d-> A::[...]: _a=1,_b=2
*/