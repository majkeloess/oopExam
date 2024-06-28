#include <iostream>

namespace A
{
  extern "C" int x;
};

namespace B
{
  extern "C" int x;
};

int A::x = 0;

int main()
{
  std::cout << B::x;
  A::x = 1;
  std::cout << B::x;
}

// extern "C": To specyfikator łączenia, który instruuje kompilator, aby używał konwencji nazewnictwa i wywoływania funkcji typowych dla języka C, zamiast konwencji C++.
// W C++ nazwy funkcji i zmiennych są zazwyczaj "dekorowane"(modyfikowane)przez kompilator, aby uwzględnić informacje o typach argumentów i przestrzeniach nazw.extern "C" zapobiega temu procesowi.