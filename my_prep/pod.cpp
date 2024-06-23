#include <type_traits>
#include <iostream>
#include <vector>
#include <deque>

class A
{
};

class A_
{
public:
  virtual ~A_() {}
};

template <typename T1, typename T2>
void my_copy(T1 beg, T1 end, T2 begg)
{
  if (std::is_pod<typename T1::value_type>::value)
  {
    std::cout << "Copying POD objects" << std::endl;
  }
  else
  {
    std::cout << "Copying Non-POD objects" << std::endl;
  }
}

int main()
{

  // prosze wykorzystac te informacje
  std::integral_constant<bool, true> tA = std::is_pod<A>::type();
  std::integral_constant<bool, false> tA_ = std::is_pod<A_>::type();

  // Iterator dla każdego kontenera ma zdefiniowany
  // typ value_type określający typ obiektu na który wskazuje
  std::deque<A> vA1;
  std::vector<A> vA2;
  my_copy(vA1.begin(), vA1.end(), vA2.begin());

  std::vector<A_> vA_1;
  std::deque<A_> vA_2;
  my_copy(vA_1.begin(), vA_1.end(), vA_2.begin());
}