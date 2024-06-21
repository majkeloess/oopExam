#include <cstdlib>
#include <iostream>
// namespace std
// {
//   class vector
//   {
//   };
//   class list
//   {
//   };
//   class deque
//   {
//   };
//   class set
//   {
//   };
//   class map
//   {
//   };
// }

namespace oop
{
  template <typename T>
  class Array
  {
  private:
    int m_size{};
    int m_index{};
    T *m_ptr{};

  public:
    using value_type = T;
    Array(int size) : m_size{size}, m_ptr{new T[size]} {}

    T &operator[](unsigned idx) const
    {
      return m_ptr[idx];
    }

    Array &insert(T el)
    {
      m_ptr[m_index] = el;
      m_index++;
      return *this;
    }

    Array &operator+(T el)
    {
      return insert(el);
    }

    int operator~()
    {
      return m_size;
    }

    ~Array()
    {
      m_index = 0;
      m_size = 0;
      delete[] m_ptr;
      m_ptr = nullptr;
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