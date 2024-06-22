#include <iostream>
#include <utility>

template <typename T>
class Smart
{
private:
  T *m_ptr{};

public:
  explicit Smart(T *ptr) : m_ptr{ptr} {}

  Smart(const Smart &other) = delete;
  Smart(Smart &&other) noexcept : m_ptr{other.m_ptr}
  {
    other.m_ptr = nullptr;
  }
  Smart &operator=(const Smart &other) = delete;

  T &operator*()
  {
    return *m_ptr;
  }

  const T &operator*() const
  {
    return *m_ptr;
  }

  T *operator->() const
  {
    return m_ptr;
  }

  ~Smart()
  {
    delete m_ptr;
    m_ptr = nullptr;
  }
};

int main()
{
  const Smart<int> p1(new int(5));
  Smart<int> p2(new int(10));

  std::cout << "p1: " << *p1 << std::endl;
  std::cout << "p2: " << *p2 << std::endl;

  //*p1 = 6; // Odkomentowanie powinno powodować błąd kompilacji
  *p2 = 15;

  std::cout << "p2 after change: " << *p2 << std::endl;

  Smart<int> p3 = std::move(p2);
  std::cout << "p3 (moved from p2): " << *p3 << std::endl;

  // std::cout << *p2 << std::endl; // Odkomentowanie powinno powodować błąd wykonania

  // Smart<int> p4 = p1; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
p1: 5
p2: 10
p2 after change: 15
p3 (moved from p2): 15
*/

// 2 sposób:

// T operator*()
// {
//   return *m_ptr;
// }

// T &operator*() const
// {
//   return *m_ptr;
// }