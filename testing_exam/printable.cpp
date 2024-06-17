#include <iostream>
#include <string>

struct is_printable
{
  virtual void print(std::ostream &os) const = 0; // Czysta funkcja wirtualna
};

std::ostream &operator<<(std::ostream &os, const is_printable &obj)
{
  obj.print(os);
  return os;
}

struct A : public is_printable
{
  std::string s;
  A(const std::string &s) : s(s) {}
  void print(std::ostream &os) const override { os << s; }
};

struct B : public is_printable
{
  int x;
  B(int x) : x(x) {}
  void print(std::ostream &os) const override { os << x; }
};

int main()
{
  A a("Tekst");
  B b{123};
  std::cout << "a:\t" << a << "; b:\t" << b << "\n";
  const is_printable &a_r = a;
  const is_printable &b_r = b;
  std::cout << "a_r:\t" << a_r << "; b_r:\t" << b_r << "\n";
}

/*
a:      Tekst; b:       123
a_r:    Tekst; b_r:     123
*/

// Zadanie:

// Twoim zadaniem jest prawdopodobnie :

// Zaimplementować klasę is_printable :

// Zdefiniuj klasę abstrakcyjną is_printable,
// która będzie miała czystą funkcję wirtualną do wypisywania zawartości obiektów.Zaimplementować klasy A i B :

// Spraw,
// aby klasy A i B dziedziczyły po is_printable.Zaimplementuj w nich metodę(lub operator),
// która będzie wypisywać ich dane na strumień wyjściowy.Przeciążyć operator<<(opcjonalnie) :

//                                                                                            Możesz(ale nie musisz) przeciążać operator<< dla klas A,
// B i is_printable,
// aby umożliwić ich bezpośrednie wypisywanie na std::cout.