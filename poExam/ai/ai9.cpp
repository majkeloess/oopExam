int main()
{
  const Fraction f1(1, 2);
  Fraction f2(3, 4);

  std::cout << "f1: " << f1 << std::endl;
  std::cout << "f2: " << f2 << std::endl;

  Fraction f3 = f1 + f2;
  std::cout << "f1 + f2 = " << f3 << std::endl;

  f2 *= 2;
  std::cout << "f2 * 2 = " << f2 << std::endl;

  std::cout << "f1 < f2: " << (f1 < f2) << std::endl;

  // f1 += f2; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
f1: 1/2
f2: 3/4
f1 + f2 = 5/4
f2 * 2 = 3/2
f1 < f2: 1
*/