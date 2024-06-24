#include "ThreeNum.h"

int main()
{
  ThreeNum t1(1, 2, 3);

  std::cout << "t1: " << t1 << std::endl;

  ThreeNum sum = t1 + t1;
  std::cout << "Suma: " << sum << std::endl;

  ThreeNum product = t1 * t1;
  std::cout << "Iloczyn: " << product << std::endl;

  ThreeNum doubled = t1 * 2;
  std::cout << "Podwojona trójka: " << doubled << std::endl;

  double ave = t1.Ave();
  std::cout << "Ave: " << ave << std::endl;

  return 0;
}
