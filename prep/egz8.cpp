using Float_t = Type_t<>;


int main()
{
    using Type_t = ptr<std::pair<Float_t, Float_t>>;

    Type_t t1{new Type_t::value_type{}};
    // Type_t t2 = t1;
    // Type_t t2; t2 = t1;
    // Type_t t2 = new Type_t::value_type();
    // Powyższe się mają nie kompilować
    (*t1).first = Type_t::value_type::first_type{1.};
    t1->second = Type_t::value_type::second_type{2.5};

    Type_t t2 = std::move(t1);

    // t3=std::move(t2); 
    const Type_t t3{new Type_t::value_type{}};                                 
    //(*t3).first= 13;
    // t3->second = 13;
    // Powyższe się mają nie kompilować
    (*t3).first = Type_t::value_type::first_type{1};  
    t3->second = Type_t::value_type::second_type{2.5};

    
    std::cout << (*t3).first._v << ", " << t3->second << std::endl;
}
/* output:
1, 2.5
*/