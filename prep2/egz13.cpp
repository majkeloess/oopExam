#include <iostream>
#include <string>

struct is_printable{
  virtual std::ostream &print(std::ostream &out) const = 0;

  friend std::ostream &operator<<(std::ostream &out, const is_printable &pri)
  {
    return pri.print(out);
  } 
};


struct A : is_printable{
  std::string m_str{};
  A(const std::string &str) : m_str{str} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << m_str;
    return out;
  }
};

struct B : is_printable{
  int m_val{};
  B(int val) : m_val{val} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << m_val;
    return out;
  }
};




int main()
{
  A a ("Tekst"); B b {123};
  std::cout<< "a:\t"<<a<<"; b:\t"<<b<<"\n";
  const is_printable & a_r = a; const is_printable & b_r = b;
   std::cout<< "a_r:\t"<<a_r<<"; b_r:\t"<<b_r<<"\n";
}

/*
a:      Tekst; b:       123
a_r:    Tekst; b_r:     123
*/