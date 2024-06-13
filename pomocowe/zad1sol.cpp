#include<iostream>
#include<vector>

struct Base{
  virtual std::ostream& print(std::ostream&) const = 0;
};

struct Derived1 : Base{
  std::ostream& print(std::ostream& os) const{
    return os<<__PRETTY_FUNCTION__;
  }
};

struct Derived2 : Base{
  std::ostream& print(std::ostream& os) const{
    return os<<__PRETTY_FUNCTION__;
  }
};

struct Derived3 : Derived2{
  std::ostream& print(std::ostream& os) const{
    return os<<__PRETTY_FUNCTION__;
  }
};

std::ostream& operator<<(std::ostream& os, Base& v){
  return v.print(os);
}

std::ostream& operator<<(std::ostream& os, std::vector<Base*> v){
  os<<"[\n";
  for(auto el: v){
    el->print(os);
    os<<"\n";
  }
  os<<"]\n";
  return os;
}


int main(){
    Derived1 d1;
    Derived3 d3;
    Derived2 d2 = d3;
    // Derived1 d1_make_err = d2;

    // std::vector<Base> v_make_err = {d1, d2, d3};
    std::vector<Base*> v = {&d1, &d2, &d3};

    std::cout << *v.front()<<std::endl;
    std::cout << v;
}