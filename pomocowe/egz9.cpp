#include <iostream>
#include <utility>

class A
{
private:
    int _a{};
    int _b{};

public:
    A()
    {
        std::cout << __PRETTY_FUNCTION__ << " _a=" << _a << ",_b=" << _b << std::endl;
    }
    explicit A(int a) : _a{a}
    {
        std::cout << __PRETTY_FUNCTION__ << " _a=" << _a << ",_b=" << _b << std::endl;
    }
    A(int a, int b) : _a{a}, _b{b}
    {
        std::cout << __PRETTY_FUNCTION__ << " _a=" << _a << ",_b=" << _b << std::endl;
    }
    A(const A &other) = delete;
    A(A &&other)
    {
        _a = other._a;
        _b = other._b;
        std::cout << __PRETTY_FUNCTION__ << " _a=" << _a << ",_b=" << _b << std::endl;
    }
};

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