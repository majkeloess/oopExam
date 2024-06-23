#include <iostream>
#include <functional>

// template <typename Fun>
// void my_for_each(int *beg, int *end, Fun fun)
// {
//   for (int *it = beg; it != end; ++it)
//   {
//     fun(it);
//   }
//   std::cout << std::endl;
// }

// template <typename Iter>
// void my_for_each(Iter beg, Iter end, std::function<void(int)> fun)
// {
//   for (Iter it = beg; it != end; ++it)
//   {
//     fun(*it);
//   }
// }

template <typename Iter, typename Fun>
void my_for_each(Iter beg, Iter end, Fun fun)
{
  for (Iter it = beg; it != end; ++it)
  {
    fun(it);
  }
}

int main()
{
  using namespace std;
  int c[] = {1, 2, 3, 4, 5};

  auto print = [](int *i)
  { std::cout << *i << " "; };

  auto print_eol = []()
  { std::cout << std::endl; };

  my_for_each(begin(c), end(c), print);

  print_eol();

  int add_value = 1;

  auto add = [&add_value](int *i)
  {
    *i += add_value;
  };

  my_for_each(begin(c), end(c), add);
  my_for_each(begin(c), end(c), print);
  print_eol();

  add_value = 10;

  my_for_each(begin(c), end(c), add);
  my_for_each(begin(c), end(c), print);
  print_eol();
}

/// Output : 1 2 3 4 5\n2 3 4 5 6\n 12 13 14 15 16 * /