#include <iostream>
#include <algorithm>
#include <vector>

// napisać własny np. zbliżony do for_each, biorący wszystkie kontenery
template <typename T>
void print_val(T &val)
{
  std::cout << val << " ";
}

namespace majkeloess
{

  template <typename Iter, typename Function>
  void for_each(Iter beg, Iter end, Function function)
  {
    for (Iter i = beg; i < end; i++)
    {
      function(*i);
    }
    std::cout << std::endl;
  }
}

int main()

{
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  majkeloess::for_each(std::begin(vec), std::end(vec), print_val<std::vector<int>::value_type>);
  std::for_each(std::begin(vec), std::end(vec), print_val<std::vector<int>::value_type>);
  std::cout << std::endl;
  std::cout << std::distance(std::begin(vec), std::end(vec)); // odległość między ite, zwróci tu 10
  std::cout << std::endl;

  return 0;
}