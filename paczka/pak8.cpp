#include <iostream>
#include <typeinfo>

struct A
{
  virtual ~A() { std::cout << "~A()\n"; }
};

template <typename T>
struct B : A
{
  T v;
  B() : v(T()) {}
  B(const B &) { std::cout << "Copy " << typeid(B).name() << "\n"; }
  ~B() { std::cout << "~" << typeid(B).name() << "\n"; }
};

int main()
{
  typedef B<A> B_A;
  typedef B<B_A> TypeName;
  TypeName a = TypeName(TypeName());
  TypeName b = a;

  return 0;
}
