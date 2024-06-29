#include <iostream>
#include <iterator>
#include <deque>
#include <set>
#include <list>

using namespace std;

template <typename InputIterator>
void przesun(InputIterator &itr, int dist, std::random_access_iterator_tag)
{
  itr += dist;
}
template <typename InputIterator>
void przesun(InputIterator &itr, int dist, std::bidirectional_iterator_tag)
{
  if (dist >= 0)
  {
    while (dist > 0)
    {
      itr++;
      dist--;
    }
  }
  else
  {
    while (dist < 0)
    {
      itr--;
      dist++;
    }
  }
}
template <typename InputIterator>
void advance1(InputIterator &itr, int dist)
{
  typename std::iterator_traits<InputIterator>::iterator_category trait;
  przesun(itr, dist, trait);
};

int main()
{
  std::deque<int> d;
  std::set<int> s;
  std::list<double> l;
  for (int i = 0; i < 10; i++)
  {
    d.push_back(i);
    s.insert(i);
    l.push_back(i);
  }
  std::deque<int>::iterator ditr = d.begin();
  std::set<int>::iterator sitr = s.begin();
  std::list<double>::iterator litr = l.begin();

  std::cout << "Deque: " << *ditr << ", ";
  advance1(ditr, 5);
  std::cout << *ditr << std::endl;

  std::cout << "Set: " << *sitr << ", ";
  advance1(sitr, 5);
  std::cout << *sitr << std::endl;

  std::cout << "List: " << *litr << ", ";
  advance1(litr, 5);
  std::cout << *litr << std::endl;

  return 0;
}
