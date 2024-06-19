
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

struct A
{
  static int m_val;
  void operator()(int &i)
  {
    m_val--;
    i += m_val;
  }
};

int A::m_val = 0;
// zmienną statyczną mogę zadeklarować w klasie ale nie mogę jej inicjalizować

int main()
{
  std::list<int> coll(11);
  std::for_each(std::begin(coll), std::end(coll), A());
  copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, "; "));
  return 0;
}
// to ma się wyświetlić:
//  -1; -2; -3; -4; -5; -6; -7; -8; -9; -10; -11;
