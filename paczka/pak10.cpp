#include <iostream>

int main()
{
  auto fun = []
  { std::cout << "Test: " << __PRETTY_FUNCTION__ << std::endl; };
  fun();
  auto fun_name = typeid(fun).name();
  std::cout << fun_name << std::endl;
  return 0;
}
