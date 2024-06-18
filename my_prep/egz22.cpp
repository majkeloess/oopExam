#include <iostream>

struct A
{

  A() = default;

  int i{};
};

template <typename T>
struct ptr
{

  ptr() = default;
  ptr(const ptr &other) = delete;
  ptr &operator=(const ptr &other) = delete;
  explicit ptr(T *pointer) : m_ptr{pointer} {}

  friend bool operator==(const ptr &pt1, const ptr &pt2)
  {
    return pt1.m_ptr == pt2.m_ptr;
  }

  friend bool operator!=(const ptr &pt1, const ptr &pt2)
  {
    return pt1.m_ptr != pt2.m_ptr;
  }

  T *operator->() const
  {
    return m_ptr;
  }

  T &operator*() const
  {
    return *m_ptr;
  }

private:
  T *m_ptr{};
};

int main()
{
  const ptr<A> a(new A);
  const ptr<A> b;
  ptr<A> c(new A);

  // ptr<A> _b_error = new A;   // Odkomentowanie powoduje błąd kompilacji
  // a = a;                     // Odkomentowanie powoduje błąd kompilacji
  // const ptr<A> _c_error = a; // Odkomentowanie powoduje błąd kompilacji

  std::cout << (((*a).i, a->i)) << " " << ++c->i << " ";
  std::cout << (a == ptr<A>()) << " " << (a != b) << "\n";
}