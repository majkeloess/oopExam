#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
class Para
{
public:
  Para(const T &a = T(), const T &b = T()) : first(a), second(b) {}
  string print() const
  {
    ostringstream out;
    out << first << " : " << second << endl;
    return out.str();
  }

private:
  T first, second;
};

ostream &operator<<(ostream &out, const vector<Para<int>> &coll)
{
  for (int i = 0; i < coll.size(); i++)
  {
    out << coll[i].print();
  }
  return out;
}
/*UZU*/
typedef vector<Para<int>> ParyInt;

int main(void)
{
  ParyInt Dane[5];

  for (unsigned i = 1; i < 5; i++)
    Dane[0].push_back(Para<int>(i, 2 * i));
  for (unsigned i = 1; i < 6; i++)
    Dane[1].push_back(Para<int>(i, 3 * i));
  for (unsigned i = 1; i < 7; i++)
    Dane[2].push_back(Para<int>(i, 4 * i));
  std::cout << "Dane[0]:\n"
            << Dane[0] << std::endl;
  std::cout << "Dane[1]:\n"
            << Dane[1] << std::endl;
  std::cout << "Dane[2]:\n"
            << Dane[2] << std::endl;
}

/*
Dane[0]:
1 : 2
2 : 4
3 : 6
4 : 8

Dane[1]:
1 : 3
2 : 6
3 : 9
4 : 12
5 : 15

Dane[2]:
1 : 4
2 : 8
3 : 12
4 : 16
5 : 20
6 : 24
*/
