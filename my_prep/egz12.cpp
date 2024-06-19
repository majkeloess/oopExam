#include <iostream>
#include <array>
#include <string>
#include <memory>
#include <algorithm>

template <typename T>
void my_print(std::array<std::unique_ptr<T>, 2> &arr)
{
  std::cout << "[";
  std::for_each(arr.begin(), arr.end(), [](const std::unique_ptr<T> &el)
                { std::cout << *el << ";"; });
  std::cout << "]\n";
}

template <typename T>
void my_print(std::array<std::unique_ptr<T>, 2> &arr, const std::string &str1, const std::string &str2)
{
  std::cout << "[";
  std::for_each(arr.begin(), arr.end(), [&str1](const std::unique_ptr<T> &el)
                { std::cout << *el << str1; });
  std::cout << "]" << str2;
}

template <typename T>
void my_swap(T &el1, T &el2)
{
  std::swap(el1, el2);
}

int main()
{
  std::array<std::unique_ptr<int>, 2> a = {
      std::unique_ptr<int>(new int{1}),
      std::unique_ptr<int>(new int{2})};

  // my_print_el("----------------\n");
  my_print(a, ";", " -> ");
  my_swap(a[0], a[1]);
  my_print(a, ";", " -> ");
  my_swap(*a[0], *a[1]);
  my_print(a);
  // my_print_el("----------------");
}
//[1;2;] -> [2;1;] -> [1;2;]