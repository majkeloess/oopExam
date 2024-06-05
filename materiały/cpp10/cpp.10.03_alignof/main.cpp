#include <iostream>
 
struct Foo {
    int   i;
    float f;
    char  c;
};
 
struct Empty {};
 
struct alignas(64) Empty64 {};
 
struct alignas(16) Double { 
    double d;    
};
 
int main()
{
    std::cout << "Alignment of"  "\n"
        "- bool             : " << alignof(bool)    << "\n"
        "- char             : " << alignof(char)    << "\n"
        "- pointer          : " << alignof(int*)    << "\n"
        "- double           : " << alignof(double)  << "\n"
        "- class Foo        : " << alignof(Foo)     << "\n"
        "- empty class      : " << alignof(Empty)   << "\n"
        "- alignas(64) Empty: " << alignof(Empty64) << "\n"
        "- alignas(1) Double: " << alignof(Double)  << '\n';
}