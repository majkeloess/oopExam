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

// template <typename T>
// void my_swap(T &el1, T &el2)
// {
//   std::swap(el1, el2);
// }

// template <typename Container>
// void my_print(const Container &c, const std::string &str1, const std::string &str2)
// {
//   std::cout << "[";
//   for (auto it = std::begin(c); it != std::end(c); ++it)
//   {
//     std::cout << *it << str1;
//   }
//   std::cout << "]" << str2;
// }

// template <typename Container>
// void my_print(const Container &c)
// {
//   std::cout << "[";
//   for (auto it = std::begin(c); it != std::end(c); ++it)
//   {
//     std::cout << *it << ";";
//   }
//   std::cout << "]";
// }

// template <typename T>
// void my_swap(T &val1, T &val2)
// {
//   T temp = val1;
//   val1 = val2;
//   val2 = temp;
// }

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