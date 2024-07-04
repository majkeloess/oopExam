#include<iostream>

class A
{
public:
    A(){std::cout<<__PRETTY_FUNCTION__<<"\n";}
    ~A(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

class B : virtual public A
{
public:
    B(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~B(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

class X:public A, virtual public B
{
public:
    X(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~X(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

class Y: public X, virtual public B
{
public:
    Y(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~Y(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

class Z: public Y, virtual public X
{
public:
    Z(){std::cout<<__PRETTY_FUNCTION__<<"\n";}
    ~Z(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

int main() {Z z;}