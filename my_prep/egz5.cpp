#include <algorithm>
#include <iostream>
#include <list>

auto f1 = [](auto val){
  std::cout << " " << val;
};

// void f1(int val)
// {
//   std::cout << " " << val;
// }
auto f2 = [](auto val)
{
  if (val % 2 == 0)
    std::cout << " " << val;
};

struct f3
{
  int m_val{};
  f3(int val) : m_val{val} {}
  void operator()(int &i)
  {
    i += m_val;
  }
};

template <typename Iter, typename Fun>
void print_to_if(std::ostream &out, Iter beg, Iter end, Fun fun)
{
  out;
  for (Iter i = beg; i != end; i++)
  {
    fun(*i);
  }
  std::cout << std::endl;
}

template <typename Iter, typename Fun>
void change(Iter beg, Iter end, Fun fun)
{
  std::for_each(beg, end, fun);
}

int main()
{
  const auto cl = {1, 2, 3, 4, 5, 6, 7};

  print_to_if(std::cout << "All: ", begin(cl), end(cl), f1);
  print_to_if(std::cout << "All: ", begin(cl), end(cl), f2);

  int add_value{-1};
  std::list<int> cl2 = {7, 6, 5, 4, 3, 2, 1};
  change(begin(cl2), end(cl2), f3{add_value});
  print_to_if(std::cout << "All  ", begin(cl2), end(cl2), f1);
}
/*
All: 1 2 3 4 5 6 7
All: 2 4 6
All  6 5 4 3 2 1 0
*/