/* W zadaniu nalezy poprawnie odwzorowac zaleznosci dziedziczenia wielokrotnego między klasami.

   UWAGA: Klasa bazowa NIE dostarcza wspólnego interfejsu.
   UWAGA: Przemyśleć implementację operatora <<.
 */
#include <iostream>
// #include "Mebel.h"
// #include "Sofa.h"
// #include "Lozko.h"
// #include "Kanapa.h"

class Mebel
{
protected:
  int m_sz{}, m_wys{}, m_dl{};

public:
  Mebel(int sz, int wys, int dl)
      : m_sz{sz}, m_wys{wys}, m_dl{dl}
  {
  }

  virtual std::ostream &print(std::ostream &out) const
  {
    out << "jakis mebel Mebel: " << m_sz << ", " << m_wys << ", " << m_dl << std::endl;
    return out;
  }

  virtual ~Mebel()
  {
    std::cout << "~Mebel" << std::endl;
  }

  friend std::ostream &operator<<(std::ostream &out, const Mebel &meb);
};

std::ostream &operator<<(std::ostream &out, const Mebel &meb)
{
  return meb.print(out);
}

class Sofa : virtual public Mebel
{
protected:
  int m_sie{};

public:
  Sofa(int sz, int wys, int dl, int sie)
      : Mebel{sz, wys, dl}, m_sie{sie}
  {
  }
  std::ostream &print(std::ostream &out) const override
  {
    out << "jakas sofa Sofa: " << m_sz << ", " << m_wys << ", " << m_dl << ", " << m_sie << std::endl;
    return out;
  }

  virtual ~Sofa()
  {
    std::cout << "~Sofa" << std::endl;
  }
};

class Lozko : virtual public Mebel
{
protected:
  int m_spa{};

public:
  Lozko(int sz, int wys, int dl, int spa)
      : Mebel{sz, wys, dl}, m_spa{spa}
  {
  }
  std::ostream &print(std::ostream &out) const override
  {
    out << "jakas lozko Lozko: " << m_sz << ", " << m_wys << ", " << m_dl << ", " << m_spa << std::endl;
    return out;
  }

  virtual ~Lozko()
  {
    std::cout << "~Lozko" << std::endl;
  }
};

class Kanapa : public Lozko, public Sofa
{
public:
  Kanapa(int sz, int wys, int dl, int sie, int spa)
      : Lozko{sz, wys, dl, spa}, Sofa{sz, wys, dl, sie}, Mebel{sz, wys, dl}
  {
  }
  std::ostream &print(std::ostream &out) const override
  {
    out << "jakas kanapa Kanapa: " << m_sz << ", " << m_wys << ", " << m_dl << ", " << m_sie << ", " << m_spa << std::endl;
    return out;
  }

  virtual ~Kanapa()
  {
    std::cout << "~Kanapa" << std::endl;
  }
};

int main()
{
  {
    Mebel m(100, 120, 150);
    std::cout << "jakis mebel " << m << std::endl;
  }

  {
    Sofa *s = new Sofa(90, 100, 200, 180);
    Mebel *x = s;
    std::cout << "jakas sofa " << *x << std::endl;
    delete x;
  }

  {
    Lozko *l = new Lozko(90, 100, 200, 190);
    const Mebel *x = l;
    std::cout << "king bed " << *x << std::endl;
    delete x;
  }

  { // wykorzystanie własności wielokrotnego dziedziczenia
    Kanapa *k = new Kanapa(80, 90, 220, 195, 200);
    Sofa *s = k;
    Lozko *l = k;
    //    l = 0;

    std::cout << "kanapa z ikei " << *s << std::endl;
    delete s;
  }
}
/* wynik
jakis mebel Mebel: sz:100 wys:120 dl:150
~Mebel
jakas sofa Sofa: Mebel: sz:90 wys:100 dl:200  siedzisko: 180
~Sofa
~Mebel
king bed Lozko: Mebel: sz:90 wys:100 dl:200  sz.spania: 190
~Lozko
~Mebel
kanapa z ikei jako Mebel: sz:80 wys:90 dl:220
 jako Sofa: Mebel: sz:80 wys:90 dl:220  siedzisko: 195
 jako Lozko: Mebel: sz:80 wys:90 dl:220  sz.spania: 200
~Kanapa
~Lozko
~Sofa
~Mebel

 */