#include <iostream>
#include <type_traits>

struct A{
  int i = 1;
  A() = default;
};


template <typename T>
struct ptr{
  T *m_ptr{};
  ptr() = default;
  explicit ptr(T *ptr) : m_ptr{ptr} {}
  ptr(const ptr &other) = delete;
  ptr &operator=(const ptr &other) = delete;

  T *operator->() const
  {
    return m_ptr;
  }

  T &operator*() const
  {
    return *m_ptr;
  }
  
  T *operator->()
  {
    return m_ptr;
  }

  T &operator*()
  {
    return *m_ptr;
  }

  friend bool operator==(const ptr &ptr1, const ptr &ptr2)
  {
    return ptr1.m_ptr == ptr2.m_ptr;
  }

  friend bool operator!=(const ptr &ptr1, const ptr &ptr2)
  {
    return ptr1.m_ptr != ptr2.m_ptr;
  }

  ~ptr() {
    delete m_ptr;
    m_ptr = nullptr;
  }
};


int main() {
  const ptr<A>  a(new A);
  const ptr<A> b;
  ptr<A> c(new A);

  // ptr<A>  _b_error = new A;      // Odkomentowanie powoduje błąd kompilacji 
  // a = a;               // Odkomentowanie powoduje błąd kompilacji 
  // const ptr<A> _c_error = a;     // Odkomentowanie powoduje błąd kompilacji 

  std::cout << (((*a).i, a->i))        << " " << ++c->i << " ";
  std::cout << (a == ptr<A>() ) << " " << (a != b) << "\n";
}
// 1 2 0 1