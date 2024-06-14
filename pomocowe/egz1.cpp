#include <iostream>

class A
{
public:
    A() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~A() { std::cout << __PRETTY_FUNCTION__ << "; "; }
};

class B : virtual public A
{
public:
    B() { std::cout << __PRETTY_FUNCTION__ << "; "; }
    ~B() { std::cout << __PRETTY_FUNCTION__ << "; "; }
};

class X : public A, virtual public B
{
public:
    X() { std::cout << __PRETTY_FUNCTION__ << "; "; }
    ~X() { std::cout << __PRETTY_FUNCTION__ << "; "; }
};

class Y : public X, virtual public B
{
public:
    Y() { std::cout << __PRETTY_FUNCTION__ << "; "; }
    ~Y() { std::cout << __PRETTY_FUNCTION__ << "; "; }
};

class Z : public Y, virtual public X
{
public:
    Z() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~Z() { std::cout << __PRETTY_FUNCTION__ << "; "; }
};

int main() { Z z; }

// egz1.cpp:17:7: warning: direct base ‘A’ inaccessible in ‘X’ due to ambiguity [-Winaccessible-base]
// 17 | class X : public A, virtual public B | ^egz1.cpp : 31 : 7 : warning : direct base ‘X’ inaccessible in ‘Z’ due to ambiguity[-Winaccessible - base] 31 | class Z : public Y, virtual public X |

// Dziedziczenie Diamentowe :
// Twoje klasy tworzą wzorzec "diamentu" :
// Z dziedziczy z Y i X. Zarówno Y,
// jak i X dziedziczą z B.B i X(niewirtualnie) dziedziczą z A.
//
// Niejednoznaczność : To tworzy dwie potencjalne ścieżki dojścia do A z Z :
//     Z->Y->X->A
//     Z->Y->B->A
// Konsekwencje : Ponieważ dziedziczenie z A jest niewirtualne w co najmniej jednej ze ścieżek, kompilator nie wie, którą ścieżkę wybrać, aby uzyskać dostęp do elementów członkowskich A.To powoduje ostrzeżenia i problemy z kolejnością konstruowania / niszczenia obiektów.

// Wyjaśnienie Zmian:
//  X dziedziczy wirtualnie z A, Z dziedziczy wirtualnie z X