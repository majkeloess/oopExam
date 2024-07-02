#include <iostream>
#include <deque>

template <typename T = int, template <typename U = T, typename Allocator = std::allocator<U>> class StorageType = std::deque>
struct fifo
{
  using storage_type = StorageType<T>;
  storage_type storage;

  void push(T val)
  {
    storage.push_back(val);
  }

  T get()
  {
    T val = storage.front();
    storage.erase(storage.begin());
    return val;
  }

  size_t size() const
  {
    return storage.size();
  }

  typename storage_type::const_iterator begin() const //nie storage tylko storage type
  {
    return storage.begin();
  }

  typename storage_type::const_iterator end() const  
  {
    return storage.end();
  }

};

int main()
{
  fifo<> ft;
  for (int i : {0, 1, 2, 3, 4})
    ft.push(i);

  fifo<int, std::deque> f = ft;

  std::cout << f.get();
  std::cout << f.size();

  for (fifo<>::storage_type::const_iterator i = f.begin(); i != f.end(); ++i)
    std::cout << *i << ",";
}
/*
  Wynik:
  fifo<T, StorageType>::fifo() [with T = int, StorageType = std::deque]
  0
  4
  1,2,3,4,
*/