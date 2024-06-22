#include <iostream>
#include <vector>

template <typename T>
class Stack
{
private:
  std::vector<T> m_stack{};

public:
  size_t size() const
  {
    return m_stack.size();
  }

  T top() const
  {
    re
  }
};

int main()
{
  const Stack<int> s1;
  Stack<int> s2;

  s2.push(1);
  s2.push(2);
  s2.push(3);

  std::cout << "s1 size: " << s1.size() << std::endl;
  std::cout << "s2 size: " << s2.size() << std::endl;

  std::cout << "s2 top: " << s2.top() << std::endl;

  s2.pop();
  std::cout << "s2 after pop, size: " << s2.size() << std::endl;

  const Stack<int> s3 = s2;
  std::cout << "s3 size: " << s3.size() << std::endl;

  // s1.push(5); // Odkomentowanie powinno powodować błąd kompilacji
  // s3.pop(); // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
s1 size: 0
s2 size: 3
s2 top: 3
s2 after pop, size: 2
s3 size: 2
*/