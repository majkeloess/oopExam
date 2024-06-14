#include <iostream>

// w całym kodzie można bezpośrednio wywoływać tylko dwie funkcje: printOn i operator <<
// wypisywanie może się odbywać tylko z wykorzystaniem __PRETTY_FUNCTION__ i "\n"
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu

struct B
{
protected:
  friend std::ostream &operator<<(std::ostream &os, const B &o);
  virtual std::ostream &printOn(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, const B &o)
{
  return o.printOn(os);
}

std::ostream &B::printOn(std::ostream &os) const
{
  return os << __PRETTY_FUNCTION__ << "\n";
}

class D1 : public B
{
protected:
  std::ostream &printOn(std::ostream &os) const
  {
    return os << __PRETTY_FUNCTION__ << "\n";
  }
};

struct D2 : D1
{
};

class D3 : public D1
{
protected:
  std::ostream &printOn(std::ostream &os) const
  {
    return os << __PRETTY_FUNCTION__ << "\n";
  }
};

struct D4 : D3
{
protected:
  std::ostream &printOn(std::ostream &os) const
  {
    B::printOn(os);
    D1::printOn(os);
    D3::printOn(os);
    return os << __PRETTY_FUNCTION__ << "\n";
  }
};

int main(int argc, char *argv[])
{
  // B b;
  //  odkomentowanie powoduje błąd kompilacji
  D1 d1;
  D2 d2;
  D3 d3;
  const D4 d4;
  std::cout << "d1: " << d1 << "d2: " << d2 << "d3: " << d3 << "d4: " << d4;
}

/* Output:
d1: [...] D1::printOn[...]
d2: [...] D1::printOn[...]
d3: [...] D3::printOn[...]
d4: [...] B::printOn[...]
[...] D1::printOn[...]
[...] D3::printOn[...]
[...] D4::printOn[...]
*/
