#include <string>
#include <iostream>
#include <utility>

struct A {
  std::string s {"test"};
  A() = default;
  A(const A &o) : s(o.s) { std::cout << "move failed, copying!\n"; }
  A(A &&o) : s(std::move(o.s)) { std::cout << "moving!\n"; }
  A &operator=(const A &other) {
    s = other.s;
    std::cout << "copy assigned\n";
    return *this;
  }
  A &operator=(A &&other) {
    s = std::move(other.s);
    std::cout << "move assigned\n";
    return *this;
  }
};

A f() { return A{}; }

struct B : A {
  std::string s2;
  int n;

};

struct C : B {
  ~C() {} 
};

struct D : B {
  D() {}
  ~D() {} 
  D &operator=(D &&) = default; 
};

int main() {
  A a1, a2;
  std::cout << "Trying to move-assign A from rvalue temporary\n";
  a1 = f(); // move-assignment from rvalue temporary
  std::cout << "Trying to move-assign A from xvalue\n";
  a2 = std::move(a1); // move-assignment from xvalue

  std::cout << "\nTrying to move-assign B\n";
  B b1, b2;
  std::cout << "Before move, b1.s = \"" << b1.s << "\"\n";
  b2 = std::move(b1); // calls implicit move assignment
  std::cout << "After move, b1.s = \"" << b1.s << "\"\n";

  std::cout << "\nTrying to move-assign C\n";
  C c1, c2;
  c2 = std::move(c1); // calls the copy assignment operator

  std::cout << "\nTrying to move-assign D\n";
  D d1, d2;
  d2 = std::move(d1);
}