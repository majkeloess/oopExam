#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  // std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};                  // WERSJA 1
  std::vector<double> c = {1.6, 2.6, 3.6, 4.6, 5.6, 6.6, 7.6};

  std::cout << "c: ";
  std::for_each(std::begin(c), std::end(c), [](auto val){std::cout << val << " ";} );

  std::cout << "\nc wieksze od 3.5: ";
  std::for_each(std::begin(c), std::end(c), [](auto val){if(val > 3.5) std::cout << val << " ";});

  std::cout << "\nc posortowane: ";
  std::sort(std::begin(c), std::end(c), [](const auto a, const auto b){return a > b;} );
  std::for_each(std::begin(c), std::end(c), [](auto val){std::cout << val << " ";});

  std::cout << "\nc dodane 'x': ";
  decltype(*std::begin(c)) x = *std::begin(c);

  std::for_each(std::begin(c), std::end(c), [x](auto &val){val+=x;} );
  std::for_each(std::begin(c), std::end(c), [](auto val){std::cout << val << " ";});

  auto f = [&x](auto val){ x+=val; return x;};
  std::cout << "\nx: " << x << " ";
  std::cout << "f: " << f(6) << " ";
  std::cout << "x: " << x << std::endl;
}

/*
c: 1.6 2.6 3.6 4.6 5.6 6.6 7.6
c wieksze od 3.5: 3.6 4.6 5.6 6.6 7.6
c posortowane: [7.6] [6.6] [5.6] [4.6] [3.6] [2.6] [1.6]
c dodane 'x': 15.2, 14.2, 13.2, 12.2, 11.2, 10.2, 9.2
x: 7.6 f: 13.6 x: 13.6
*/