#include <iostream>

int main()
{
  std::cout << +!!"";
}

// Starting from the right, "" is a string literal, which gets converted to a pointer, which gets converted to a bool with the value true.This then gets passed to two operator!s, which flip it to false and back to true again.Finally, operator+ converts the bool true to the int 1, which gets printed.