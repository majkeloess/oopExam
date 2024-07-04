#include <iostream>

// uzupelnij tutaj

int main()
{
  CarFactory &fordFactory = CarFactory::getInstance("ford");
  CarFactory &fordFactory2 = CarFactory::getInstance("ford");
  CarFactory &toyotaFactory = CarFactory::getInstance("toyota");

  Car greenFord = fordFactory.createCar("zielony");
  Car redToyota = toyotaFactory.createCar("czerwony");

  std::cout << greenFord << redToyota << (&fordFactory == &fordFactory2) << std::endl;

  // poniższy kod powoduje błąd kompilacji

  // CarFactory customFactory("wlasna");
  // CarFactory namelessFactory;

  // Car customCar("wlasny");
  // Car namelessCar;
}
// Wyjscie:
// Samochod marki ford w kolorze zielony
// Samochod marki toyota w kolorze czerwony
// 1