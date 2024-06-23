#include <iostream>

template <typename T>
class SharedPtr
{
private:
  T *m_ptr{};
  size_t m_count{};

public:
  explicit SharedPtr(T *ptr) : m_ptr{ptr} {}

  size_t use_count() const
  {
    return m_count;
  }

  const T &operator*() const
  {
    return *m_ptr;
  }

  T &operator*()
  {
    return *m_ptr;
  }
};

int main()
{
  const SharedPtr<int> p1(new int(5));
  SharedPtr<int> p2(new int(10));

  std::cout << "*p1: " << *p1 << std::endl;
  std::cout << "*p2: " << *p2 << std::endl;

  SharedPtr<int> p3 = p2;
  *p3 = 15;

  std::cout << "*p2 after change through p3: " << *p2 << std::endl;
  std::cout << "p2 use count: " << p2.use_count() << std::endl;

  p2.reset(new int(20));
  std::cout << "*p2 after reset: " << *p2 << std::endl;
  std::cout << "*p3 after p2 reset: " << *p3 << std::endl;

  //*p1 = 6; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
*p1: 5
*p2: 10
*p2 after change through p3: 15
p2 use count: 2
*p2 after reset: 20
*p3 after p2 reset: 15
*/