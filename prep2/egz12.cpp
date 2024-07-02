#include<iostream>
#include<array>
#include<string>
#include <memory>

void my_print(std::array<std::unique_ptr<int>,2> &arr, const std::string &str1, const std::string &str2)
{
  std::cout << "[";
  for (size_t i=0; i < arr.size(); ++i)
  {
    std::cout << *arr[i] << str1;
  }
  std::cout << "]" << str2;
}

void my_print(std::array<std::unique_ptr<int>,2> &arr)
{
  std::cout << "[";
  for (size_t i=0; i < arr.size(); ++i)
  {
    std::cout << *arr[i] << ";";
  }
  std::cout << "]";
}


template <typename T>
void my_swap(T &val1, T &val2)
{
  std::swap(val1, val2);
}


int main()
{
  std::array<std::unique_ptr<int>,2> a = {
      std::unique_ptr<int>(new int {1}),
      std::unique_ptr<int>(new int {2})
      };

  my_print(a,";"," -> ");
  my_swap(a[0],a[1]);
  my_print(a,";"," -> ");
  my_swap(*a[0],*a[1]);
  my_print(a);
}
//[1;2;] -> [2;1;] -> [1;2;]