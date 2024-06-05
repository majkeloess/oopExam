#include <iostream>
#include <memory>
#include <type_traits>
#include "../type.hpp"

struct Base
{ virtual void Fun(){} };// = 0; };

struct Base2
{ virtual ~Base2() = default; virtual void Fun() = 0; };


struct Derived : Base {
    ~Derived() { std::cout << "Derived::~Derived\n"; }

    void Fun() { std::cout << "Derived::Fun\n"; }
};

struct Derived2 : Base2 {
    ~Derived2() { std::cout << "Derived2::~Derived2\n"; }

    void Fun() { std::cout << "Derived2::Fun\n"; }
};



int main()
{ 
  std::cout << "---------------- Derived ----------------\n";
  {
    std::cout << "***** std::shared_ptr:";
    std::cout << " type: Derived *****\n";
    std::shared_ptr<Base> ptr(new Derived);// std::shared_ptr<Base> ptr = std::make_shared<Derived>();
    ptr->Fun();
  }

  {
    std::cout << "***** std::shared_ptr from ordinary ptr";
    std::cout << " type: Derived *****\n";
    typename std::add_pointer<Base>::type o_ptr = new Derived;

    std::shared_ptr<Base> ptr(o_ptr);
    ptr->Fun();

  }

  {
    std::cout << "***** std::unique_ptr";
    std::cout << " type: Derived *****\n";
    std::unique_ptr<Base> ptr = std::make_unique<Derived>();
    ptr->Fun();
  }

  std::cout << "---------------- Derived2 ----------------\n";
  {
    std::cout << "***** std::shared_ptr:";
    std::cout << " type: Derived2 *****\n";
    std::shared_ptr<Base2> ptr(new Derived2);
    ptr->Fun();
  }

  {
    std::cout << "***** std::shared_ptr from ordinary ptr";
    std::cout << " type: Derived2 *****\n";
    typename std::add_pointer<Base2>::type o_ptr = new Derived2;

    std::shared_ptr<Base2> ptr(o_ptr);
    ptr->Fun();

  }

  {
    std::cout << "***** std::unique_ptr";
    std::cout << " type: Derived2 *****\n";
    std::unique_ptr<Base2> ptr = std::make_unique<Derived2>();
    ptr->Fun();
  }

}


// The type of &derived::f will be void (base::*)(), not void (derived::*)(). 
// This was already true in C++03, but it was impossible to get the base class type without actually specifying it. 
// With decltype, it's easy and only needs this little function:

// https://stackoverflow.com/questions/8709340/can-the-type-of-a-base-class-be-obtained-from-a-template-type-automatically

// unimplemented to make sure it's only used
// in unevaluated contexts (sizeof, decltype, alignof)
template<typename T, typename U>
T base_of(U T::*);


//
template<typename T>
void explain(T t = T()) noexcept {
  std::cout 
    << "------------- Type: " 
    << type<T>() 
    << " -------------\n"
    << std::boolalpha
    << "has_virtual_destructor: "
    << std::has_virtual_destructor<T>()
    << "\n";
    // << "--------------------------\n";
}

//warunek wyjścia
inline void test(){}

// variadic tampelate
template<typename T, typename... Args>
inline void test(T a, Args... args){

  // explain(a);
  {
    std::cout << "***** std::shared_ptr" ;
    std::cout << " type: "<< type<T>() << " *****\n";
    std::shared_ptr<decltype(base_of(&T::Fun))> ptr = std::make_shared<T>();
    ptr->Fun();
  }

  {
    std::cout << "***** std::shared_ptr from ordinary ptr";
    std::cout << " type: "<< type<T>() << " *****\n";
    typename std::add_pointer<decltype(base_of(&T::Fun))>::type o_ptr = new T;

    std::shared_ptr<decltype(base_of(&T::Fun))> ptr(o_ptr);
    ptr->Fun();

  }

  {
    std::cout << "***** std::unique_ptr";
    std::cout << " type: "<< type<T>() << " *****\n";
    std::unique_ptr<decltype(base_of(&T::Fun))> ptr = std::make_unique<T>();
    ptr->Fun();
  }

  test(args...);

}
