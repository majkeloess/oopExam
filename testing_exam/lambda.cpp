#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

// ewentualnie zamiast std::function zrobić klasę szablonową

// template <typename Function>
class liftToVector
{
public:
  std::function<int(int)> m_f;
  liftToVector(std::function<int(int)> f)
      : m_f{f}
  {
  }

  std::vector<int> operator()(std::vector<int> vec)
  {
    std::vector<int> newVec;
    for (auto &el : vec)
    {
      newVec.emplace_back(m_f(el));
    }
    return newVec;
  }
};

int main()
{
  // add2 funkcja lambda, która dodaje dwa do elementu

  auto add2 = [](int val)
  { return val += 2; };

  auto vadd2 = liftToVector(add2);

  // tworzenie vectora int
  std::vector<int> x = {0, 9, 4};

  // zwraca vector typu int z wartości przekazanych do x
  auto v = vadd2(x);

  std::for_each(v.begin(), v.end(), [](const int n)
                { std::cout << n << ' '; });

  return 0;
}
// 2 11 6