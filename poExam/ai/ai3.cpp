#include <iostream>
#include <tuple>
#include <string>

// Tutaj napisz potrzebne funkcje i klasy

template <typename T>
std::string format_tuple(T tuple)
{
  std::string retStr;
  for (size_t i = 0; i < std::tuple_size<decltype(tuple)>::value; i++)
  {
    retStr += std::to_string(std::get<i>(tuple));
    retStr += ",";
  }

  return retStr;
}

int main()
{
  const auto t = std::make_tuple(42, 3.14, std::string("Hello"));

  std::cout << "Tuple: " << format_tuple(t) << std::endl;
  // std::cout << "Sum of elements: " << sum_tuple_elements(t) << std::endl;

  return 0;
}

// Tuple: (42, 3.14, Hello)
// Sum of elements : 45.14