namespace std{
  class vector{};
  class list{};
  class deque{};
  class set{};
  class map{};
}

#include<cstdlib>
#include <iostream>

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