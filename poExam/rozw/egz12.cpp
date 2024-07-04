#include <iostream>
#include <array>
#include <string>
#include <memory>

void my_print(std::array<std::unique_ptr<int>, 2> &arr, const std::string &str1, const std::string &str2)
{
  std::cout << "[";
  for (auto &el : arr)
  {
    std::cout << *el << str1;
  }
  std::cout << "]" << str2;
}

void my_print(std::array<std::unique_ptr<int>, 2> &arr)
{
  std::cout << "[";
  for (auto &el : arr)
  {
    std::cout << *el << ";";
  }
  std::cout << "]" << "\n";
}

template <typename El>
void my_swap(El &el1, El &el2)
{
  std::swap(el1, el2);
}

int main()
{
  std::array<std::unique_ptr<int>, 2> a = {
      std::unique_ptr<int>(new int{1}),
      std::unique_ptr<int>(new int{2})};

  my_print(a, ";", " -> ");
  my_swap(a[0], a[1]);
  my_print(a, ";", " -> ");
  my_swap(*a[0], *a[1]);
  my_print(a);
}
//[1;2;] -> [2;1;] -> [1;2;]