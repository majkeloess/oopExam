#include<iostream>
#include<vector>


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

/*Wynik:
virtual std::ostream& Derived1::print(std::ostream&) const
[
virtual std::ostream& Derived1::print(std::ostream&) const,
virtual std::ostream& Derived2::print(std::ostream&) const,
virtual std::ostream& Derived3::print(std::ostream&) const
]
*/