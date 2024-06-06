#include <iostream>
#include <cmath>

class Figura
{
public:
  virtual std::ostream &print(std::ostream &out) const = 0;
  virtual double pole() const = 0;
  virtual double obw() const = 0;

  virtual ~Figura()
  {
  }

  friend std::ostream &operator<<(std::ostream &out, const Figura &f);
};

std::ostream &operator<<(std::ostream &out, const Figura &f)
{
  return f.print(out);
}

class Prostokat : public Figura
{
private:
  double m_a{}, m_b{};

public:
  Prostokat(double a, double b) : m_a{a}, m_b{b} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << "Prostokat: " << m_a << ", " << m_b << " Pole: " << pole() << " Obw: " << obw() << std::endl;
    return out;
  }
  double pole() const override
  {
    return m_a * m_b;
  }
  double obw() const override
  {
    return 2 * (m_a + m_b);
  }
};

class Kwadrat : public Prostokat
{
private:
  double m_a{};

public:
  Kwadrat(double a) : Prostokat{a, a}, m_a{a} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << "Kwadrat: " << m_a << " Pole: " << pole() << " Obw: " << obw() << std::endl;
    return out;
  }
};

class Trojkat : public Figura
{
private:
  double m_a{}, m_b{}, m_c{};

public:
  Trojkat(double a, double b, double c) : m_a{a}, m_b{b}, m_c{c} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << "Trojkat: " << m_a << ", " << m_b << ", " << m_c << " Pole: " << pole() << " Obw: " << obw() << std::endl;
    return out;
  }
  double pole() const override
  {
    double x = (m_a + m_b + m_c) / 2;
    return sqrt(x * (x - m_a) * (x - m_b) * (x - m_c));
  }
  double obw() const override
  {
    return m_a + m_b + m_c;
  }
};

class Kolo : public Figura
{
private:
  double m_r{};

public:
  Kolo(double r) : m_r{r} {}
  std::ostream &print(std::ostream &out) const override
  {
    out << "Kolo: " << m_r << ", Pole: " << pole() << " Obw: " << obw() << std::endl;
    return out;
  }
  double pole() const override
  {
    return 3.14 * m_r * m_r;
  }
  double obw() const override
  {
    return 2 * 3.14 * m_r;
  }
};

int main()
{
  Prostokat p = Prostokat(1, 2);
  Kwadrat kw = Kwadrat(3);
  Trojkat t = Trojkat(3, 4, 5);
  Kolo ko = Kolo(2);

  std::cout << p << std::endl;
  std::cout << kw << std::endl;
  std::cout << t << std::endl;
  std::cout << ko << std::endl;
}

// Prostokąt o bokach a=1.000000, b=2.000000, Pole: 2.000000, Obwód: 6.000000
// Kwadrat o boku a=3.000000, Pole: 9.000000, Obwód: 12.000000
// Trójkąt o bokach a=3.000000, b=4.000000,c =5.000000, Pole: 6.000000, Obwód: 12.000000
// Koło o promieniu 2.000000, Pole: 12.566371, Obwód: 12.566371