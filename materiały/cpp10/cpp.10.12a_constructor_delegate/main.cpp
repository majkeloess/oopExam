
struct A {

  A(double a, double b) 
    : _a(a), _b(b)
  {}

  A(double a) : A(a, 0.0) 
  {}

  A() : A(0.0, 0.0) 
  {}

  A(double a, double b, int times) : A(a*times, b*times)
  {}

private:
  double _a, _b;
};


int main() {

  A a, b(1.0), c(1,1), d(1,1,1);
}