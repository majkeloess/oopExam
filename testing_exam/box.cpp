#include <iostream>

struct Obj;
template <typename T>
struct Box; // forward declaration

struct Obj
{
  virtual void Draw() const = 0;
};

template <typename T>
struct Box : public Obj
{
  T value;

  explicit Box(const T &value) : value(value) {}
  // Próba niejawnej konwersji wartości 3 na Box<int> spowodowałaby błąd kompilacji, ponieważ konstruktor Box jest oznaczony jako explicit. Oznaczenie explicit w C++ jest stosowane przede wszystkim do konstruktorów i operatorów konwersji, aby zapobiec niejawnym konwersjom typu. Gdy konstruktor jest oznaczony jako explicit, kompilator nie będzie automatycznie konwertował argumentu na typ klasy podczas tworzenia obiektu.  Aby utworzyć obiekt klasy z argumentu innego typu, musisz użyć jawnej konwersji, np. poprzez bezpośrednie wywołanie

  void Draw() const override
  {
    std::cout << __PRETTY_FUNCTION__ << " --> " << value << std::endl;
  }

  operator T()
  {
    return value;
  }

  template <typename K>
  friend std::ostream &operator<<(std::ostream &os, const Box<K> &box);
};

template <typename K>
std::ostream &operator<<(std::ostream &os, const Box<K> &box)
{
  return os << box.value;
}

// Specjalizacja szablonu dla Box<Box<T>>, Definiuje specjalizację szablonu Box dla przypadku, gdy parametr szablonu T jest również typem Box<T>. To pozwala na tworzenie zagnieżdżonych "pudełek" (np. Box<Box<int>>

template <typename T>
struct Box<Box<T>> : public Obj
{
  Box<T> value;

  Box(const T &value) : value(Box<T>(value)) {}

  operator Box<T>() { return value; }

  void Draw() const override
  {
    std::cout << __PRETTY_FUNCTION__ << " --> " << value << std::endl;
  }

  operator T()
  {
    return value;
  }
};

int main()
{

  Box<int> b_i{3};
  Obj &r1 = b_i;
  r1.Draw();
  int i = b_i;
  Box<double> b_d{3.4};
  Obj &r2 = b_d;
  r2.Draw();
  double d = b_d;
  Box<Box<int>> bb_i{3};
  const Obj &r3 = bb_i;
  r3.Draw();
  b_i = bb_i;
  Box<Box<double>> bb_d{3.4};
  const Obj &r4 = bb_d;
  r4.Draw();
  b_d = bb_d;

  // Box<int> _ = 3; // Odkomentowanie powoduje b��d kompilacji
}
/* standardowe wyj�cie:
struct Box<int>::Draw() --> 3
struct Box<double>::Draw() --> 3.4
struct Box<Box<int>>::Draw() --> 3
struct Box<Box<double>>::Draw() --> 3.4 */

// Kiedy używać explicit?

// Konstruktory jednoargumentowe : Zazwyczaj warto oznaczać konstruktory jednoargumentowe jako explicit, chyba że masz wyraźny powód, aby zezwolić na niejawne konwersje.Operatory konwersji : Rozważ oznaczenie operatorów konwersji jako explicit, jeśli konwersja może być kosztowna lub prowadzić do utraty danych.