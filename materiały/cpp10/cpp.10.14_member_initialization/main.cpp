#include <string>
#include <iostream>
#include <utility>

struct S {
   int m;
   int n;
   int x = m + 1;  // OK: implicit this allowed in default initializers (C++11)
   int y = 5;

   S(int init) : m(init),
                 n(m - 1), // OK:implicit this allowed in member initializer lists
                 y(init)
   {}
};

int main()
{
    S s(1);

    std::cout << "s.m = " << s.m << ", s.n = " << s.n 
      << ", s.x = " << s.x << ", s.y = " << s.y << "\n";
}