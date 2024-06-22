#include <iostream>
#include <vector>
#include <algorithm>

template <typename Iter, typename Fun>
void my_for_each(Iter beg, Iter end, Fun fun)
{
  for (Iter it = beg; it != end; it++)
  {
    fun(*it);
  }
}

int main()
{
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  const auto printer = [](const int &n)
  { std::cout << n << " "; };

  std::cout << "Original vector: ";
  std::for_each(numbers.begin(), numbers.end(), printer);
  std::cout << std::endl;

  std::cout << "Squared vector: ";
  my_for_each(numbers.begin(), numbers.end(), [](int &n)
              { n *= n; });
  std::for_each(numbers.begin(), numbers.end(), printer);
  std::cout << std::endl;

  return 0;
}

// Original vector: 1 2 3 4 5
// Squared vector : 1 4 9 16 25