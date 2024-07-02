#include<iostream>
#include<vector>

class Base{
public:
    virtual std::ostream &print(std::ostream &out) const = 0;

    friend std::ostream &operator <<(std::ostream &out, const Base &base)
    {
        return base.print(out);
    }
};

class Derived1 : public Base{
public:
    Derived1() = default;
    Derived1(const Derived1 &other) = delete;
    std::ostream &print(std::ostream &out) const override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

};

class Derived2 : public Derived1{
public:
    Derived2() = default;
    std::ostream &print(std::ostream &out) const override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Derived3 : public Derived2{
public:
    Derived3() = default;
    std::ostream &print(std::ostream &out) const override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

std::ostream &operator<<(std::ostream &out, std::vector<Base*> v)
{
    out << "[" << std::endl;
    for(auto &el: v)
    {
        el->print(out);
    }
    out << "]" << std::endl;
    return out;
}





int main(){
    Derived1 d1;
    Derived3 d3;
    Derived2 d2 = d3;
    Derived1 d1_make_err = d2;

    //std::vector<Base> v_make_err = {d1, d2, d3};
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