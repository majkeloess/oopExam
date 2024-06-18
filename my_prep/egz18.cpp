#include <utility>
#include <iostream>
#include <algorithm>

template <typename T>
class ptr
{
private:
  T *m_ptr{};

public:
  using value_type = T;
  explicit ptr(T *ptr) : m_ptr{ptr} {}
  ptr(ptr &&other) noexcept : m_ptr{other.m_ptr} {}
  ptr &operator=(const ptr &other) = delete;

  T *operator->() const
  {
    return m_ptr;
  }

  T &operator*() const
  {
    return *m_ptr;
  }
};

template <typename T = float>
class Type_t
{
public:
  T _v;
  Type_t() = default;
  explicit Type_t(const T &v) : _v{v} {} // lub explicit Type_t(T v) : _v{v} {}
  // W większości przypadków najlepszym rozwiązaniem jest użycie konstruktora przyjmującego stałą referencję (const T& v). Zapewnia to największą elastyczność i pozwala na niejawne konwersje zarówno lvalue, jak i rvalue. Jak ref to zawsze const (bez modyfikacji value ofc)

  friend std::ostream &operator<<(std::ostream &out, const Type_t &t)
  {
    out << t._v;
    return out;
  }
};

using Float_t = Type_t<>;

int main()
{
  using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
  Type_ptr t1{new Type_ptr::value_type{}};
  // Type_ptr t2 = t1;
  // Type_ptr t2;
  // t2 = t1;
  // Type_ptr t3 = new Type_ptr::value_type();
  (*t1).first = Type_ptr::value_type::first_type{1};
  t1->second = Type_ptr::value_type::second_type{2.5};
  std::cout << t1->first._v << " " << t1->second << std::endl;

  Type_ptr t2 = std::move(t1);
  // t2->first = 13;
  // t2->second = 13;
  const Type_ptr t3 = std::move(t2);
  // t3->first = Type_ptr::value_type::first_type{13};
  // t3->second = Type_ptr::value_type::second_type{13};

  std::cout << (*t3).first._v << " " << (*t3).second << std::endl;
  return 0;
}

// 1 2.5
// 1 2.5