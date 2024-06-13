
#include <iostream>

class FOO
{
    public:
        virtual void func() const = 0;
};

void FOO::func() const
{
    std::cout<<"Base!";
}

class Derived : FOO
{
 public:
    void func() const override
    {
        FOO::func();
    }

};




int main()
{
Derived* x = new Derived();
x -> func();

return 0;
};