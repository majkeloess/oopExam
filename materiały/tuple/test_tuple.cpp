#include <iostream>
#include <tuple>
#include <string>

int main()
{

  std::tuple<int, std::string, double> t1(42, "hello", 3.14);
  std::tuple<int, std::string, double> t2 = std::make_tuple(42, "hello", 3.14);

  std::tuple<int, std::string> t3(1, "jeden");
  auto t5 = std::tuple_cat(t3, std::make_tuple(2.5, "dwa i pół")); // tuple cat pierwszy arg to łączenie tupli starej a do drugiego nowy
  //  t2 będzie typu std::tuple<int, std::string, double, std::string>
  std::cout << std::get<0>(t3) << std::endl;

  std::pair<int, double> example = {1, 2.5};
  std::cout << example.first << " " << example.second << std::endl;

  return 0;
}