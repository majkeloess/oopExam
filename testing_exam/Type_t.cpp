#include <iostream>

template <typename T = float>
class Type_t
{

public:
  T _v;
  Type_t() = default;
  // Type_t &operator=(const Type_t &t) = delete;
  explicit Type_t(T v) : _v{v} {}
  friend std::ostream &operator<<(std::ostream &out, const Type_t<T> &type)
  {
    out << type._v;
    return out;
  }
};

template <typename T>
class ptr
{
private:
  T *m_ptr{};

public:
  using value_type = T; // to musi być zawsze public
  ptr() = default;
  explicit ptr(T *ptr) : m_ptr{ptr} {}
  ptr(const ptr &other) = delete;
  ptr &operator=(const ptr &other) = delete;
  ptr(ptr &&other) : m_ptr{other.m_ptr} {}
  ptr &operator=(ptr &&other) = delete;

  T &operator*() const
  {
    return *m_ptr;
  }

  T *operator->() const
  {
    return m_ptr;
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
  // Type_t t2 = new Type_t::value_type();
  //  Powyższe się mają nie kompilować
  (*t1).first = Type_t::value_type::first_type{1.};
  t1->second = Type_t::value_type::second_type{2.5};

  Type_t t2 = std::move(t1);

  const Type_t t3{new Type_t::value_type{}};
  // t3 = std::move(t2);
  //(*t3).first = 13;
  // t3->second = 13;
  // Powyższe się mają nie kompilować
  (*t3).first = Type_t::value_type::first_type{1};
  t3->second = Type_t::value_type::second_type{2.5};

  std::cout << (*t3).first._v << ", " << t3->second << std::endl;
}
/* output:
1, 2.5
*/