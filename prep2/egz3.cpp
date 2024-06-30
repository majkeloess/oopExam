#include <iostream>

// w całym kodzie można bezpośrednio wywoływać tylko dwie funkcje: printOn i operator <<
// wypisywanie może się odbywać tylko z wykorzystaniem __PRETTY_FUNCTION__ i "\n"
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu

struct B
{
protected:
  virtual std::ostream &onPrint(std::ostream &out) const = 0;

  friend std::ostream &operator<<(std::ostream &out, const B &b)
  {
    return b.onPrint(out);
  }
};

std::ostream &B::onPrint(std::ostream &out) const
{
  out << __PRETTY_FUNCTION__ << "\n";
  return out;
}

struct D1 : B
{
protected:
  std::ostream &onPrint(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

struct D2 : D1
{
protected:
  std::ostream &onPrint(std::ostream &out) const override
  {
    D1::onPrint(out);
    return out;
  }
};

struct D3 : D2
{
protected:
  std::ostream &onPrint(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

struct D4 : D3
{
protected:
  std::ostream &onPrint(std::ostream &out) const override
  {
    B::onPrint(out);
    D1::onPrint(out);
    D3::onPrint(out);
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

int main(int argc, char *argv[])
{
  // B b;
  // odkomentowanie powoduje błąd kompilacji
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