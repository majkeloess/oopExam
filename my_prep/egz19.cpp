#include <iostream>
#include <deque>

template <typename T = int, template <typename U = T, typename Allocator = std::allocator<U>> class StorageType = std::deque>
struct fifo
{
  using storage_type = StorageType<T>;
  storage_type storage{};
  // Ta linia definiuje alias typu storage_type, który jest skróconą nazwą dla typu StorageType<T>. W tym przypadku StorageType to parametr szablonu, który domyślnie jest std::deque, a T to typ danych, który domyślnie jest int. Zatem, storage_type staje się synonimem dla std::deque<int>.

  void push(T &val)
  {
    storage.push_back(val);
  }

  T size()
  {
    return storage.size();
  }

  T get()
  {
    T val = storage.front();
    storage.pop_front();
    return val;
  }

  typename storage_type::const_iterator begin()
  {
    return storage.begin();
  }

  // typename storage_type::const_iterator begin() : Metoda zwracająca iterator wskazujący na początek kontenera storage.typename jest tutaj wymagane, ponieważ const_iterator jest zależnym typem szablonu(dependent type), a kompilator nie wie, czy to typ, czy wartość, dopóki nie zostanie określony parametr szablonu.

  typename storage_type::const_iterator end()
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