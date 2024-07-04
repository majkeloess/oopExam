#include <iostream>

struct Obj;
template <typename T>
struct Box;
struct Obj
{
  virtual void Draw() const = 0;
};

template <typename T = int>
struct Box : Obj
{
  T m_len{};
  explicit Box(T len) : m_len{len} {}
  void Draw() const override
  {
    std::cout << __PRETTY_FUNCTION__ << " --> " << m_len << std::endl;
  }

  operator T() const
  {
    return m_len;
  }
};

template <typename T>
struct Box<Box<T>> : Obj
{
  Box<T> m_box{};
  explicit Box(Box<T> len) : m_box{len} {}

  void Draw() const override
  {
    std::cout << __PRETTY_FUNCTION__ << " --> " << m_box << std::endl;
  }
  operator T() const
  {
    return m_box;
  }

  operator Box<T>() const
  {
    return m_box;
  }
};

int main()
{

  Box<> b_i{13};
  Obj &r_1 = b_i;
  r_1.Draw();
  int i = b_i;

  Box b_d{14.15};
  Obj &r_2 = b_d;
  r_2.Draw();
  double d = b_d;

  Box<Box<int>> bb_i{b_i};
  const Obj &r_3 = bb_i;
  r_3.Draw();
  Box<int> br_i = bb_i;

  Box<Box<double>> bb_d{b_d};
  const Obj &r_4 = bb_d;
  r_4.Draw();
  Box<double> b_a = bb_d;

  // Box<int> _ = 1;     // BŁĄD KOMPILACJI

  return 0;
}

/*
Box<i>::Draw() --> 13
Box<d>::Draw() --> 14.15
Box<3BoxIiE>::Draw() --> 13
Box<3BoxIdE>::Draw() --> 14.15
*/