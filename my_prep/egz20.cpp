#include <iostream>
#include <vector>

class Base
{
public:
  Base() = default;
  Base(const Base &b) = delete;
  virtual std::ostream &print(std::ostream &out) const = 0;
  friend std::ostream &operator<<(std::ostream &out, const Base &b)
  {
    return b.print(out);
  }

  friend std::ostream &operator<<(std::ostream &out, std::vector<Base *> v)
  {
    out << "[\n";
    for (auto &el : v)
    {
      el->print(out);
    }
    out << "]\n";

    return out;
  }
};

std::ostream &Base::print(std::ostream &out) const
{
  out << __PRETTY_FUNCTION__ << "\n";
  return out;
}

class Derived1 : public Base
{
public:
  Derived1() : Base{} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

class Derived2 : public Base
{
public:
  Derived2() : Base{} {}
  Derived2(const Derived2 &other) {}

  std::ostream &print(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

class Derived3 : public Derived2
{
public:
  Derived3() : Derived2{} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << __PRETTY_FUNCTION__ << "\n";
    return out;
  }
};

int main()
{
  Derived1 d1;
  Derived3 d3;
  Derived2 d2 = d3;
  // derived3 to klasa pochodna derived2, czyli można do niej przypisać obiekt klasy pochodnej
  // Derived2 d2 = d3;: Kopiuje obiekt d3 (Derived3) do d2 (Derived2). Ponieważ Derived3 dziedziczy po Derived2, ta operacja jest dozwolona. (To jest przykład polimorfizmu w działaniu).

  //  Derived1 d1_make_err = d2;

  //std::vector<Base> v_make_err = {d1, d2, d3};
  // żeby to nie działało trzeba w bazowej wyjebać kopiujący i dodać kopiujący w d2
  std::vector<Base *> v = {&d1, &d2, &d3};

  std::cout << *v.front() << std::endl;
  std::cout << v;
}

/*Wynik:
virtual std::ostream& Derived1::print(std::ostream&) const
[
virtual std::ostream& Derived1::print(std::ostream&) const,
virtual std::ostream& Derived2::print(std::ostream&) const,
virtual std::ostream& Derived3::print(std::ostream&) const
]
*/