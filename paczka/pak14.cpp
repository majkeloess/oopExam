/*
** Olivia
** 14.02.2011
** Klasa vector z wyjatkami
**
*/

#include <iostream>
#include "vector.h"

int main(int argc, char *argv[])
{
  Vector<double> v1;
  for (int i = 0; i < 25; ++i)
  {
    v1.push_back(0.2 * i);
    std::cout << v1[i] << " ";
  }
  std::cout << std::endl;
  Vector<double> v2;
  for (int i = 0; i < 22; ++i)
  {
    v2.push_back(0.1 * i);
    std::cout << v2[i] << " ";
  }
  std::cout << std::endl;

  Vector<double> v3 = v1;
  for (int i = 0; i < 25; ++i)
  {
    std::cout << v3[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Wektor 1. Pojemnosc: " << v1.capacity() << " Rozmiar: " << v1.size() << std::endl;
  std::cout << "Wektor 2. Pojemnosc: " << v2.capacity() << " Rozmiar: " << v2.size() << std::endl;
  std::cout << "Wektor 3. Pojemnosc: " << v3.capacity() << " Rozmiar: " << v3.size() << std::endl;

  std::cout << "Test zly indeks: " << std::endl;
  try
  {
    v1[-1];
  }
  catch (const IndexOutOfRange &e)
  {
    std::cout << e.what() << "\n";
  }

  return 0;
}
