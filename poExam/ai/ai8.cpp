int main()
{
  const SafeArray<int> arr1(5);
  SafeArray<int> arr2(3);

  arr2[0] = 1;
  arr2[1] = 2;
  arr2[2] = 3;

  const SafeArray<int> arr3 = arr2;

  std::cout << "arr1: " << arr1 << std::endl;
  std::cout << "arr2: " << arr2 << std::endl;
  std::cout << "arr3: " << arr3 << std::endl;

  try
  {
    std::cout << arr2[4] << std::endl;
  }
  catch (const std::out_of_range &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }

  SafeArray<int> arr4 = SafeArray<int>::concatenate(arr2, arr3);
  std::cout << "arr4: " << arr4 << std::endl;

  // arr1[0] = 5; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
arr1: [0, 0, 0, 0, 0]
arr2: [1, 2, 3]
arr3: [1, 2, 3]
Caught exception: Index out of range
arr4: [1, 2, 3, 1, 2, 3]
*/