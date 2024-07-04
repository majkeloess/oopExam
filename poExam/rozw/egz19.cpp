#include <iostream>
#include <deque>

template <typename T = int, template <typename U = T, typename Allocator = std::allocator<U>> class StorageType = std::deque>
struct fifo
{
  fifo()
  {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  using storage_type = StorageType<T>;
  storage_type m_fifo{};

  void push(T val)
  {
    m_fifo.push_back(val);
  }

  T get()
  {
    T val = m_fifo.front();
    m_fifo.erase(m_fifo.begin());
    return val;
  }

  typename storage_type::const_iterator begin() const
  {
    return m_fifo.begin();
  }

  typename storage_type::const_iterator end() const
  {
    return m_fifo.end();
  }

  size_t size() const
  {
    return m_fifo.size();
  }
};

int main()
{
  fifo<> ft;
  for (int i : {0, 1, 2, 3, 4})
    ft.push(i);

  fifo<int, std::deque> f = ft;

  std::cout << f.get() << std::endl;
  std::cout << f.size() << std::endl;

  for (fifo<>::storage_type::const_iterator i = f.begin(); i != f.end(); ++i)
    std::cout << *i << ",";

  std::cout << std::endl;
}
/*
  Wynik:
  fifo<T, StorageType>::fifo() [with T = int, StorageType = std::deque]
  0
  4
  1,2,3,4,
*/