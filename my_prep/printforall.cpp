#include <iostream>
#include <vector>
#include <set>

// W tym kodzie słowo kluczowe typename jest używane w pętli for w funkcji szablonowej printContainer przed Container::const_iterator. Jest to konieczne, ponieważ kompilator C++ nie może jednoznacznie określić, czy Container::const_iterator jest typem (w tym przypadku iteratorem), czy wartością statyczną (np. zmienną lub funkcją) wewnątrz klasy Container

// Rola typename: Słowo kluczowe typename informuje kompilator, że Container::const_iterator jest nazwą typu, a nie wartością. Dzięki temu kompilator może poprawnie przeanalizować kod i wygenerować odpowiednią funkcję dla każdego typu kontenera.

template <typename Container>
void printContainer(const Container &c)
{
  for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main()
{
  std::vector<int> vec = {1, 2, 3};
  std::set<std::string> set = {"hello", "world"};

  printContainer(vec); // Wypisze: 1 2 3
  printContainer(set); // Wypisze: hello world

  return 0;
}