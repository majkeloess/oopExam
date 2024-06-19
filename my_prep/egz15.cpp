#include <type_traits> // Dla std::is_pod i std::integral_constant
#include <iostream>
#include <deque>
#include <vector>

struct A
{
};
struct A_
{
  virtual ~A_() {}
};

// std::is_pod<typename T1::value_type>: To jest metafunkcja z biblioteki <type_traits>, która sprawdza, czy T1::value_type (typ elementów w kontenerze wskazywanym przez iterator T1) jest typem POD.

// .value : Jest to sposób na uzyskanie wartości logicznej(true lub false) z metafunkcji.W tym przypadku, jeśli T1::value_type jest typem POD, to std::is_pod<typename T1::value_type>::value będzie równe true, a w przeciwnym razie false.

template <typename T1, typename T2>
void my_copy(T1 begin, T1 end, T2 v)
{
  if (std::is_pod<typename T1::value_type>::value)
    std::cout << "Copying POD objects\n";
  else
    std::cout << "Copying non-POD objects\n";
}
int main()
{

  // prosze wykorzystac te informacje
  std::integral_constant<bool, true> tA = std::is_pod<A>::type();
  std::integral_constant<bool, false> tA_ = std::is_pod<A_>::type();

  // Iterator dla każdego kontenera ma zdefiniowany
  // typ value_type określający typ obiektu na który wskazuje
  std::deque<A> vA1;
  std::vector<A> vA2;
  my_copy(vA1.begin(), vA1.end(), vA2.begin());

  std::vector<A_> vA_1;
  std::deque<A_> vA_2;
  my_copy(vA_1.begin(), vA_1.end(), vA_2.begin());
}

/* output/wyjscie
Copying POD objects
Copying non-POD objects
*/
