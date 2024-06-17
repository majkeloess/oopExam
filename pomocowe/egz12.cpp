#include <iostream>
#include <array>
#include <string>
#include <memory>

// using arr_uniq_2 =  std::array<std::unique_ptr<int>,2>;
// using uniq_int = std::unique_ptr<int>;
// Takie coś trzeba zapierdolić jak bez szablonów

//Tam gdzie

void my_print_el(const std::string &str)
{
  // std::cout << str;
}

template <typename T>
void my_swap(T &a, T &b)
{
  std::swap(a, b);
}

template <typename T>
void my_print(T &arr)
{
  std::cout << "[";
  for (auto &el : arr)
  {
    std::cout << *el << ";";
  }
  std::cout << "]";
}

template <typename T>
void my_print(T &arr, const std::string &str1, const std::string &str2)
{
  std::cout << "[";
  for (auto &el : arr)
  {
    std::cout << *el << str1;
  }
  std::cout << "]" << str2;
}

int main()
{
  std::array<std::unique_ptr<int>, 2> a = {
      std::unique_ptr<int>(new int{1}),
      std::unique_ptr<int>(new int{2})};

  my_print_el("\n----------------\n");
  my_print(a, ";", " -> ");
  my_swap(a[0], a[1]);
  my_print(a, ";", " -> ");
  my_swap(*a[0], *a[1]);
  my_print(a);
  my_print_el("----------------");
}
//[1;2;] -> [2;1;] -> [1;2;]