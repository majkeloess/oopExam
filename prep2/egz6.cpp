namespace std{
  class vector{};
  class list{};
  class deque{};
  class set{};
  class map{};
}

#include<cstdlib>
#include <iostream>


namespace oop
{
  template <typename T>
  class Array{
    private:
      T *m_arr{};
      size_t m_size{};
      size_t m_index{};
    public:
      using value_type = T;
      Array(size_t size) : m_size{size}, m_arr{new T [size]} {}
      ~Array() 
      {
        delete[] m_arr;
        m_arr = nullptr;
        m_size = 0;
        m_index = 0;
      }

      Array &insert(T val)
      {
        m_arr[m_index] = val;
        m_index++;
        return *this;
      }

      Array &operator+(T val)
      {
        return insert(val);
      }

      T &operator[](size_t index) const 
      {
        return m_arr[index];
      }

      size_t operator~() const
      {
        return m_index;
      }
  };

};



int main(){

    typedef oop::Array<char> type;
    type a( rand() % 10 + 6 );

    a.insert('#').insert('C') + type::value_type('+') + '+' + '0' + ('0' + 3 );

    for(unsigned i = 0; i!= ~a; ++i)
      std::cout<< a[i] << (i+1 != ~a ? "" : "\n"  );
}

/*
  #C++03
*/