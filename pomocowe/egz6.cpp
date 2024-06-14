#include <cstdlib>
#include <iostream>
namespace std
{
  class vector
  {
  };
  class list
  {
  };
  class deque
  {
  };
  class set
  {
  };
  class map
  {
  };
}

namespace oop
{
  template <typename T>
  class Array
  {
  private:
    T *m_array{};
    int m_size{};
    int m_index{};

  public:
    using value_type = T;
    Array(int size)
        : m_size{size}, m_array{new T[size]}
    {
    }

    Array &insert(T val)
    {
      m_array[m_index] = val;
      m_index++;
      return *this;
    }

    T operator[](int index)
    {
      return m_array[index];
    }

    Array &operator+(T val)
    {
      return insert(val);
    }

    int operator~()
    {
      return m_size;
    }
  };
}

int main()
{

  typedef oop::Array<char> type;
  type a(rand() % 10 + 6); // od 6 do 15

  a.insert('#').insert('C') + type::value_type('+') + '+' + '0' + ('0' + 3);

  for (unsigned i = 0; i != ~a; ++i)
    std::cout << a[i] << (i + 1 != ~a ? "" : "\n");
}

/*
  #C++03
*/