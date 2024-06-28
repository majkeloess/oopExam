
#include <future>
#include <iostream>

int main()
{
  try
  {
    std::promise<int> p;
    std::future<int> f1 = p.get_future();
    std::future<int> f2 = p.get_future();
    p.set_value(1);
    std::cout << f1.get() << f2.get();
  }
  catch (const std::exception &e)
  {
    std::cout << 2;
  }
}

// The program is guaranteed to output : 2
// You can only get a future from a promise once. Trying to get it again throws future_­error.
