#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};

  std::cout << "c: ";
  std::for_each(c.begin(), c.end(),[](int val){std::cout << val << " ";} ); //wypisywanie

  std::cout << "\nc parzyste: ";
  std::for_each(c.begin(), c.end(), [](int val){if(val % 2 ==0)std::cout << val << " ";}); //wypisywanie parzystych

  std::cout << "\nc malejaco: ";
  std::sort(c.begin(), c.end(), [](const int a, const int b){ return a > b;}); //sortowanie malejaca
  std::for_each(c.begin(), c.end(), [](int val){std::cout << "[" << val << "] ";}); //wypisywanie z nawiasami kwadratowymi

  std::cout << "\nc + x: ";
  int x = 5;
  std::for_each(c.begin(), c.end(), [x](int &val){val += x;}); // kopia zwiekszone o 5
  std::for_each(c.begin(), c.end(), [](int val){std::cout << val << " ";}); //wypisywanie

  auto f = [&x](int val){x+=val; return x;}; // dodaje 6 do elementu przez ref
  std::cout << "\nx: " << x << " ";
  std::cout << "f: " << f(6) << " ";
  std::cout << "x: " << x << std::endl;
}
/*
c: 1 2 3 4 5 6 7
c parzyste: 2 4 6
c malejaco: [7] [6] [5] [4] [3] [2] [1]
c + x: 12, 11, 10, 9, 8, 7, 6,
x: 5 f: 11 x: 11
*/