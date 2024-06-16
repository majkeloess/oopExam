#include <iostream>
#include <string>

class is_printable
{

  virtual std::ostream &print(std::ostream &out) const = 0;

  friend std::ostream &operator<<(std::ostream &out, const is_printable &prin)
  {
    return prin.print(out);
  }
};

class A : public is_printable
{
private:
  std::string m_t{};

public:
  A(const std::string &str) : m_t{str} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << m_t;
    return out;
  }
};
class B : public is_printable
{
private:
  int m_val{};

public:
  B(int val) : m_val{val} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << m_val;
    return out;
  }
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