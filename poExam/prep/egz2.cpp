#include <iostream>
#include <utility>



using Float_t = Type_t<>;

int main(){
    using Type_ptr = ptr<std::pair<Float_t, Float_t>>;

    Type_ptr t1 { new Type_ptr::value_type{}};
    //Type_ptr t2 = t1;
    // Type_ptr t2; t2 = t1; 
    // Type_ptr t3 = new Type_ptr::value_type();
    (*t1).first = Type_ptr::value_type::first_type{1};
    t1->second = Type_ptr::value_type::second_type{2.5};
    std::cout<< t1->first._v<<" "<<t1->second<<std::endl;

    Type_ptr t2 = std::move(t1);
    // t2->first = 13; //tu byłby potrzebny konstruktor (Float_t) - Type_t(float v)
    // t2->second = 13;
    const Type_ptr t3 = std::move(t2);
    //t3->first = Type_ptr::value_type::first_type{13}; // tu potrzebaby drugi op.->() z const... (wtedy by się kompilowało, ale przez const t3 i tak 13 nie byłoby przypisywane)
    // t3->second = Type_ptr::value_type::second_type{13}; 

    std::cout<< (*t3).first._v<<" "<<(*t3).second<<std::endl; // tutaj możliwe, że było coś innego, ale wydaje się git
    return 0;
}