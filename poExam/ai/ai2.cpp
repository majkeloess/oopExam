#include <iostream>
#include <utility>

template <typename T1, typename T2>
struct MyPair
{
  T1 m_first{};
  T2 m_second{};

  MyPair(T1 first, T2 second) : m_first{first}, m_second{second} {}

  friend std::ostream &operator<<(std::ostream &out, const MyPair<T1, T2> &mypair)
  {
    out << "(" << mypair.m_first << ", " << mypair.m_second << ")\n";
    return out;
  }

  friend MyPair<T2, T1> swap_pair(const MyPair<T1, T2> &mypair)
  {
    MyPair<T2, T1> new_pair(mypair.m_second, mypair.m_first);
    return new_pair;
  }
};

int main()
{
  const MyPair<int, std::string> p1(42, "Hello");
  const MyPair<double, char> p2(3.14, 'A');

  std::cout << "p1: " << p1 << std::endl;
  std::cout << "p2: " << p2 << std::endl;

  auto swapped_p1 = swap_pair(p1);
  std::cout << "Swapped p1: " << swapped_p1 << std::endl;

  return 0;
}
// p1: (42, Hello)
// p2 : (3.14, A)
// Swapped p1 : (Hello, 42)