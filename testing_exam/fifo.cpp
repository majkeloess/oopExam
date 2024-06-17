#include <iostream>
#include <deque>

// Pierwszy parametr szablonu (typename T = int):
// Określa typ danych, które będą przechowywane w kolejce FIFO.Domyślnie ustawiony na int, co oznacza, że jeśli nie podasz innego typu, kolejka będzie przechowywać liczby całkowite.

// Drugi parametr szablonu(template <...> class StorageType = std::deque) :

//  Ten parametr jest nieco bardziej skomplikowany, ponieważ sam jest szablonem.Definiuje on typ kontenera, który będzie używany do przechowywania danych w kolejce FIFO.
// typename U = T : Parametr szablonu StorageType o nazwie U.Domyślnie ustawiony na T,
// co oznacza, że typ danych w kontenerze będzie taki sam jak typ danych w kolejce.typename Allocator = std::allocator<U> : Parametr szablonu StorageType określający alokator pamięci dla kontenera.Domyślnie ustawiony na standardowy alokator std::allocator.class StorageType = std::deque : Określa domyślny typ kontenera, którym jest std::deque(kolejka dwukierunkowa).Możesz to zmienić, np.na std::list(lista dwukierunkowa).

template <typename T = int, template <typename U = T, typename Allocator = std::allocator<U>> class StorageType = std::deque>
struct fifo
{
  using storage_type = StorageType<T>;
  storage_type storage;

  void push(const T &val)
  {
    storage.push_back(val);
  }

  T get()
  {
    T val = storage.front();
    storage.pop_front();
    return val;
  }

  int size()
  {
    return storage.size();
  }

  typename storage_type::const_iterator begin()
  {
    return storage.begin();
  }

  typename storage_type::const_iterator end()
  {
    return storage.end();
  }
};

// fifo<> f1;                       // Kolejka FIFO dla int, używa std::deque
// fifo<double> f2;                 // Kolejka FIFO dla double, używa std::deque
// fifo<std::string, std::list> f3; // Kolejka FIFO dla string, używa std::list

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