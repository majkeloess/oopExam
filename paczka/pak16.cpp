#include <iostream>
#include <algorithm>

struct f
{
  f() {}
  bool operator()(char &a)
  {
    a = a - 32;
  }
};
template <typename T>
void for_each(std::string &beg, int size, T fun)
{
  for (int i = 0; i < size; i++)
  {
    fun(beg[i]);
  }
}
void copy(std::string &beg)
{
  std::string str = beg;
  beg.clear();
  for (int i = str.size() - 1; i != -1; i--)
  {
    beg += str[i];
  }
}
// Uzupelnij #1
int main()
{
  std::string col = "maly tekst";
  for_each(col, col.size(), /*Uzupelnic #2*/ f());
  copy(col /*uzupelnic #3*/);
  std::cout << col;
}
/*
output:
TSKET YLAM
*/
