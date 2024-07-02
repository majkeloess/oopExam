#include <iostream>

struct Obj{
  
  virtual void Draw() const = 0;
  virtual ~Obj() {}

};

template <typename T = int>
struct Box : Obj{
  T m_val{};
  explicit Box(T val) : m_val{val} {}

  void Draw() const override
  {
    std::cout << "Box<" << typeid(m_val).name() << ">::Draw --> " << m_val << std::endl;
  }

  operator T() const 
  {
    return m_val;
  }

  friend std::ostream &operator<<(std::ostream &out, const Box &box)
  {
    out << box.m_val;
    return out;
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
}

/*
Box<i>::Draw() --> 13
Box<d>::Draw() --> 14.15
Box<3BoxIiE>::Draw() --> 13
Box<3BoxIdE>::Draw() --> 14.15
*/