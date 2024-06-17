#include<iostream>

struct A{
    A(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~A(){std::cout<<__PRETTY_FUNCTION__<<";\n";}
};

struct B: virtual A{
    B(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~B(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

struct X: virtual  B{
    X(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~X(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

struct Y: B{
    Y(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
    ~Y(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

struct Z:  X, Y{
    Z(){std::cout<<__PRETTY_FUNCTION__<<";\n";}
    ~Z(){std::cout<<__PRETTY_FUNCTION__<<"; ";}
};

int main() {Z z;}