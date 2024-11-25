struct Obj;
template <typename T>
struct Box;

#include <iostream>
struct Obj
{
  virtual void Draw() const = 0; // zamiast `=0` można `{}` dać
};

template <typename T = int> // bez `=int` wywala `Box<>`
struct Box : Obj
{
  T _v;
  explicit Box(T v) : _v(v) {}
  virtual ~Box() {}
  void Draw() const
  {
    std::cout << "Box<" << typeid(_v).name() << ">::Draw() --> " << _v << "\n";
    // std::cout << __PRETTY_FUNCTION__ << " --> " << _v << '\n'; // zwraca „void Box<T>::Draw() const [with T = Box<double>]”
  }
  operator T()
  { // nie trzeba consta
    return _v;
  }
  friend std::ostream &operator<<(std::ostream &os, const Box b)
  { // albo `const Box&` albo `Box`
    return os << b._v;
  }
};

int main()
{

  Box<> b_i{13};
  Obj &r_1 = b_i;
  r_1.Draw();
  int i = b_i;
  Box b_d{14.15};
  Obj &r_2 = b_d;
  r_2.Draw();
  double d = b_d;
  Box<Box<int>> bb_i{b_i};
  const Obj &r_3 = bb_i;
  r_3.Draw();
  Box<int> br_i = bb_i;
  Box<Box<double>> bb_d{b_d};
  const Obj &r_4 = bb_d;
  r_4.Draw();
  Box<double> b_a = bb_d;
  // Box<int> _ = 1;     // BŁĄD KOMPILACJI
}

/*
Box<i>::Draw() --> 13
Box<d>::Draw() --> 14.15
Box<3BoxIiE>::Draw() --> 13
Box<3BoxIdE>::Draw() --> 14.15
*/

// Ten kod faktycznie nie wymaga jawnej specjalizacji szablonu Box dla przypadku Box<Box<T>>, ponieważ kompilator C++ jest w stanie automatycznie wygenerować odpowiednią specjalizację na podstawie ogólnego szablonu.

// W tym konkretnym przypadku, jawna specjalizacja szablonu nie jest konieczna, ponieważ ogólny szablon Box jest wystarczająco elastyczny, aby obsłużyć również zagnieżdżone typy Box<Box<T>>. Kompilator automatycznie generuje odpowiednie specjalizacje w razie potrzeby.

// W tym przypadku kompilator jest w stanie wydedukować specjalizację szablonu Box<Box<int>>, ponieważ typ argumentu przekazanego do konstruktora (Box<int>) jednoznacznie wskazuje na tę specjalizację. Dzięki temu nie musisz jawnie definiować specjalizacji, a kod nadal działa poprawnie.