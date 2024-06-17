#include <iostream>
#include <array>
#include <string>
#include <memory> //do uniq

void my_print_el(const std::string &s)
{
  std::cout << s;
}

template <typename T, typename U>
void my_swap(T &el1, U &el2)
{
  std::swap(el1, el2);
}
template <typename T, typename U, typename V>
void my_print(std::array<std::unique_ptr<T>, 2> &arr, const U &printer1, const V &printer2)
{
  std::cout << "[";
  for (auto &el : arr)
  {
    std::cout << *el << printer1;
  }
  std::cout << "] " << printer2;
}

template <typename T>
void my_print(std::array<std::unique_ptr<T>, 2> &arr)
{
  std::cout << "[";
  for (auto &el : arr)
  {
    std::cout << *el << ";";
  }
  std::cout << "]";
}

int main()
{
  // worzy tablicę o nazwie a, która może przechowywać dokładnie 2 elementy. Każdy element jest typu std::unique_ptr<int>, czyli inteligentnego wskaźnika, który zarządza pamięcią dla pojedynczej liczby całkowitej.
  // {std::unique_ptr<int>(new int{1}), std::unique_ptr<int>(new int{2})} : Inicjalizuje tablicę a dwoma inteligentnymi wskaźnikami.Pierwszy wskaźnik wskazuje na nowo zaalokowaną liczbę całkowitą o wartości 1, a drugi na liczbę o wartości 2.

  std::array<std::unique_ptr<int>, 2> a = {
      std::unique_ptr<int>(new int{1}),
      std::unique_ptr<int>(new int{2})};

  my_print_el("----------------\n");
  my_print(a, ";", " -> ");
  my_swap(a[0], a[1]);
  my_print(a, ";", " -> ");
  my_swap(*a[0], *a[1]);
  my_print(a);
  my_print_el("\n----------------\n");
}
//[1;2;] -> [2;1;] -> [1;2;]

// W pętli for (auto& el : arr), el jest referencją do elementu tablicy a, a nie do wartości przechowywanej przez std::unique_ptr. Aby uzyskać dostęp do wartości wskazywanej przez std::unique_ptr, musisz użyć operatora wyłuskania (*), czyli *el.