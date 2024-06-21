#include <iostream>
#include <vector>

int main()
{

  std::vector<int> vec;
  std::vector<int>::value_type x = 5;            // x jest typu int
  std::vector<int>::size_type size = vec.size(); // size jest typu size_t
  std::vector<int>::iterator it = vec.begin();   // it jest iteratorem dla vector<int>
  std::cout << x << std::endl;                   // Zwraca 5
  return 0;
}