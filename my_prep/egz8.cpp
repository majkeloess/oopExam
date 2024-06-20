#include <iostream>

template <typename T = float>
class Type_t
{
public:
  T _v{};

  template <typename K>
  friend std::ostream &operator<<(std::ostream &out, const Type_t<K> &t);
};

template <typename K>
std::ostream &operator<<(std::ostream &out, const Type_t<K> &t)
{
  out << t._v;
  return out;
}

template <typename T>
class ptr
{
private:
  T *m_ptr{};

public:
  using value_type = T;
  explicit ptr(T *pointer) : m_ptr{pointer} {}
  ptr(const ptr &other) = delete;
  ptr(ptr &&other) : m_ptr{other.m_ptr} {}

  ptr &operator=(const ptr &p) = delete;
  ptr &operator=(ptr &&p) = delete;

  T *operator->() const
  {
    return m_ptr;
  }

  T &operator*() const
  {
    return *m_ptr;
  }
};

using Float_t = Type_t<>;

int main()
{
  using Type_t = ptr<std::pair<Float_t, Float_t>>;

  Type_t t1{new Type_t::value_type{}};
  // Type_t t2 = t1;
  // Type_t t2;
  // t2 = t1;
  //  Type_t t2 = new Type_t::value_type();
  //  Powyższe się mają nie kompilować
  (*t1).first = Type_t::value_type::first_type{1.};
  t1->second = Type_t::value_type::second_type{2.5};

  Type_t t2 = std::move(t1);

  const Type_t t3{new Type_t::value_type{}};
  // t3 = std::move(t2);
  //(*t3).first = 13;
  //  t3->second = 13;
  //  Powyższe się mają nie kompilować
  (*t3).first = Type_t::value_type::first_type{1};
  t3->second = Type_t::value_type::second_type{2.5};

  std::cout << (*t3).first._v << ", " << t3->second << std::endl;
}
/* output:
1, 2.5
*/