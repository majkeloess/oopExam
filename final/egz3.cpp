#include <iostream>

// w całym kodzie można bezpośrednio wywoływać tylko dwie funkcje: printOn i operator <<
// wypisywanie może się odbywać tylko z wykorzystaniem __PRETTY_FUNCTION__ i "\n"
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu

class B
{
public:
  virtual std::ostream &printOn(std::ostream &out) const = 0;

  friend std::ostream &operator<<(std::ostream &out, const B &base)
  {
    return base.printOn(out);
  }
};

class D1 : public B
{
public:
  std::ostream &printOn(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

class D2 : public D1
{
public:
  std::ostream &printOn(std::ostream &out) const override
  {
    D1::printOn(out);
    return out;
  }
};

class D3 : public D2
{
public:
  std::ostream &printOn(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

class D4 : public D3
{
public:
  std::ostream &printOn(std::ostream &out) const override
  {
    B::printOn(out);
    D1::printOn(out);
    D3::printOn(out);

    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

std::ostream &B::printOn(std::ostream &out) const
{
  out << __PRETTY_FUNCTION__ << "\n";
  return out;
}

int main(int argc, char *argv[])
{
  // B b; odkomentowanie powoduje błąd kompilacji
  D1 d1;
  D2 d2;
  D3 d3;
  const D4 d4;
  std::cout << "d1: " << d1 << "d2: " << d2 << "d3: " << d3 << "d4: " << d4;
}

/* Output:
d1: virtual std::ostream& D1::printOn(std::ostream&) const
d2: virtual std::ostream& D1::printOn(std::ostream&) const
d3: virtual std::ostream& D3::printOn(std::ostream&) const
d4: virtual std::ostream& B::printOn(std::ostream&) const
virtual std::ostream& D1::printOn(std::ostream&) const
virtual std::ostream& D3::printOn(std::ostream&) const
virtual std::ostream& D4::printOn(std::ostream&) const
*/