#include <iostream>
#include <vector>

template <typename T>
class Container
{
private:
  std::vector<T> *m_cont{};

public:
  explicit Container(size_t size)
  {
    m_cont = new std::vector<T>(size, 0);
  }

  Container(const Container &other) : m_cont{new std::vector<T>(*other.m_cont)} {}

  Container<T> &operator=(const Container &other)
  {
    if (this != &other)
    {
      m_cont = new std::vector<T>(*other.m_cont);
      delete other.m_cont;
      other.m_cont = nullptr;
    }

    return *this;
  }

  const T &operator[](unsigned index) const
  {
    return (*m_cont)[index];
  }

  T &operator[](unsigned index)
  {
    return (*m_cont)[index];
  }

  static Container<T> multiply(const Container<T> &container, T val)
  {
    Container<T> retCon = container;
    for (auto &el : *retCon.m_cont)
    {
      el *= val;
    }
    return retCon;
  }

  static int sum(const Container<T> &con1, const Container<T> &con2)
  {
    int sum = 0;

    for (size_t i = 0; i < con1.m_cont->size(); i++)
    {
      sum += (*con1.m_cont)[i] + (*con2.m_cont)[i];
    }

    return sum;
  }

  void print(const std::string &str) const
  {
    std::cout << str << "( ";
    for (auto &el : *m_cont)
    {
      std::cout << el << " ";
    }
    std::cout << ")\n";
  }

  ~Container()
  {
    delete m_cont;
    m_cont = nullptr;
  }
};

int main()
{

  const Container<int> c1(5);
  Container<int> c2(3);

  c2[0] = 1;
  c2[1] = 2;
  c2[2] = 3;

  const Container<int> c3 = c2;

  c1.print("c1: ");
  c2.print("c2: ");
  c3.print("c3: ");

  int sum = Container<int>::sum(c2, c3);
  std::cout << "Sum of c2 and c3: " << sum << std::endl;

  Container<int> c4 = Container<int>::multiply(c2, 2);
  c4.print("c4 (c2 * 2): ");

  // Container<int> error = 5; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
c1: (0, 0, 0, 0, 0)
c2: (1, 2, 3)
c3: (1, 2, 3)
Sum of c2 and c3: 12
c4 (c2 * 2): (2, 4, 6)
*/