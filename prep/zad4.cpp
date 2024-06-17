#include <iostream>

struct A { int i = 1; };

template <typename T>
class ptr{

    public:
        ptr(){}
        explicit ptr(T * a): obj(a){}
    explicit ptr(const ptr<T>& a){}
        T operator* () const{ return *obj;}

        T* operator->() const{ return obj;}

        bool operator==(const ptr<T> & a) const{
            return false;
        }

        bool operator!=(const ptr<T> & a) const{
            return true;
        }
    private:
        T * obj;
};

int main() {
  const ptr<A>  a(new A);
  const ptr<A> b;
  ptr<A> c(new A);

  //ptr<A>  _b_error = new A;      // Odkomentowanie powoduje błąd kompilacji 
  //a = a;               // Odkomentowanie powoduje błąd kompilacji 
  //const ptr<A> _c_error = a;     // Odkomentowanie powoduje błąd kompilacji 

  std::cout << (((*a).i, a->i))        << " " << ++c->i << " ";
  std::cout << (a == ptr<A>() ) << " " << (a != b) << "\n";
}