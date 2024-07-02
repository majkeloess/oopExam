#include <iostream>

struct Obj;
template <typename T>
struct Box;


struct Obj{
  virtual void Draw() const = 0;
  virtual ~Obj(){}
};

template <typename T>
struct Box : Obj{
  T m_val{};
  explicit Box(T val) : m_val{val} {}
  void Draw() const override
  {
    std::cout << __PRETTY_FUNCTION__ << " --> " << m_val << std::endl;
  }

  operator T() const   
  {
    return m_val;
  }

};


template <typename T>
struct Box<Box<T>> : Obj
{
  Box<T> m_len{};
  explicit Box(T len) : m_len{len} {}

  void Draw() const override
  {
    std::cout << __PRETTY_FUNCTION__ << " --> " << m_len << std::endl;
  }
  operator T() const
  {
    return m_len;
  }

  operator Box<T>() const
  {
    return m_len;
  }
};




int main()
{

  Box<int> b_i{3};
  Obj &r1 = b_i;
  r1.Draw();
  int i = b_i;
  Box<double> b_d{3.4};
  Obj &r2 = b_d;
  r2.Draw();
  double d = b_d;
  Box<Box<int>> bb_i{3};
  const Obj &r3 = bb_i;
  r3.Draw();
  b_i = bb_i;
  Box<Box<double>> bb_d{3.4};
  const Obj &r4 = bb_d;
  r4.Draw();
  b_d = bb_d;

  // Box<int> _ = 3; // Odkomentowanie powoduje b��d kompilacji
}
/* standardowe wyj�cie:
struct Box<int>::Draw() --> 3
struct Box<double>::Draw() --> 3.4
struct Box<Box<int>>::Draw() --> 3
struct Box<Box<double>>::Draw() --> 3.4
*/