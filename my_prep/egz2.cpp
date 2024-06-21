#include <iostream>
#include <utility>

template <typename T = float>
struct Type_t
{
  T _v{};
  Type_t() = default;
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
  using value_type = T;

  ptr() = default;
  explicit ptr(T *ptr) : m_ptr{ptr} {}
  ptr(const ptr &p) = delete;
  ptr(ptr &&p) noexcept : m_ptr{p.m_ptr}
  {
    p.m_ptr = nullptr;
  }

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
  ~ptr()
  {
    delete m_ptr;
    m_ptr = nullptr;
  }
};

using Float_t = Type_t<>;

int main()
{
  using Type_ptr = ptr<std::pair<Float_t, Float_t>>;

  Type_ptr t1{new Type_ptr::value_type{}};
  // Type_ptr t2 = t1;
  //   Type_ptr t2; t2 = t1;
  //   Type_ptr t3 = new Type_ptr::value_type();
  (*t1).first = Type_ptr::value_type::first_type{1};
  t1->second = Type_ptr::value_type::second_type{2.5};
  std::cout << t1->first._v << " " << t1->second << std::endl;

  Type_ptr t2 = std::move(t1);
  // t2->first = 13; // tu byłby potrzebny konstruktor (Float_t) - Type_t(float v)
  // t2->second = 13;
  const Type_ptr t3 = std::move(t2);
  // t3->first = Type_ptr::value_type::first_type{13}; // tu potrzebaby drugi op.->() z const... (wtedy by się kompilowało, ale przez const t3 i tak 13 nie byłoby przypisywane)
  // t3->second = Type_ptr::value_type::second_type{13};

  std::cout << (*t3).first._v << " " << (*t3).second << std::endl; // tutaj możliwe, że było coś innego, ale wydaje się git
  return 0;
}

// Konstruktor przenoszący klasy ptr ma dostęp do prywatnej składowej p.m_ptr, ponieważ jest to niezbędne do prawidłowej implementacji semantyki przenoszenia. To uprawnienie jest ograniczone do konstruktora i nie narusza zasad enkapsulacji.