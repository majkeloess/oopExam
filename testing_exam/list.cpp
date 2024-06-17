#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

class A
{
public:
  // Jest to domyślny konstruktor klasy A. W tym przypadku nie robi nic specjalnego, ale jest potrzebny, aby można było tworzyć obiekty typu A bez podawania argumentów.
  A() {}
  //: To jest przeciążenie operatora wywołania funkcji (operator()). Dzięki temu obiekty klasy A zachowują się jak funkcje i mogą być wywołane z argumentami. W tym konkretnym przypadku operator przyjmuje referencję do liczby całkowitej (int& i) i przypisuje do niej wartość statycznej zmiennej m_val, a następnie zmniejsza wartość m_val o 1.
  void operator()(int &i) const
  {
    i = m_val--;
  }
  // To jest statyczna zmienna członkowska klasy A. Zmienna statyczna istnieje tylko w jednym egzemplarzu dla całej klasy, a nie dla każdego obiektu.
  static int m_val;
};

int A::m_val = -1;

using namespace std;

int main()
{
  // Tworzy listę coll zawierającą 11 elementów typu int. Domyślnie wszystkie elementy są zainicjalizowane wartością 0.
  list<int> coll(11);

  // To jest najważniejsza linia kodu. Wywołuje ona algorytm std::for_each z biblioteki standardowej C++. Algorytm ten wykonuje podaną funkcję dla każdego elementu w zadanym zakresie. W tym przypadku zakresem jest cała lista coll, a funkcją jest obiekt tymczasowy klasy A
  for_each(std::begin(coll), std::end(coll), A());

  // Ta linia wypisuje wszystkie elementy listy coll na standardowe wyjście (std::cout), oddzielając je średnikami i spacją.
  copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, "; "));

  return 0;
}
// to ma się wyświetlić:
//  -1; -2; -3; -4; -5; -6; -7; -8; -9; -10; -11;

// W tym kodzie nie ma jawnego wywołania funktora z argumentem, ale jest on wywoływany niejawnie przez algorytm std::for_each

// W kontekście tego kodu, "obiekt tymczasowy" oznacza obiekt, który jest tworzony automatycznie przez kompilator i istnieje tylko przez krótki czas, zazwyczaj w obrębie jednego wyrażenia. W tym przypadku, obiekt tymczasowy klasy A jest tworzony podczas wywołania A(), a następnie przekazywany do algorytmu std::for_each. Po zakończeniu działania std::for_each, obiekt tymczasowy jest automatycznie niszczony.

// Dlaczego tworzony jest obiekt tymczasowy?

// Algorytm std::for_each oczekuje jako trzeciego argumentu obiektu funkcyjnego (callable object), który może być wywołany dla każdego elementu kontenera. W C++ istnieje kilka rodzajów obiektów funkcyjnych:

// Funkcje: Zwykłe funkcje mogą być przekazane do std::for_each.
// Wskaźniki do funkcji: Można również przekazać wskaźnik do funkcji.
// Funktory (obiekty funkcyjne): To obiekty klas, które przeciążają operator wywołania funkcji operator(), dzięki czemu mogą być wywołane jak funkcje.

// W tym kodzie używamy funktora, ponieważ pozwala on na przechowywanie stanu (zmiennej m_val). Gdybyśmy chcieli użyć zwykłej funkcji, musielibyśmy przekazać zmienną m_val jako dodatkowy argument do std::for_each, co byłoby mniej eleganckie.