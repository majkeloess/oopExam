#include <iostream>

class ClassA
{
public:
    ClassA(int value)
    : value_(value) {}

    int value_;
};

class Ptr
{
public:
    Ptr(ClassA* ptr)
    : ptr_(ptr) {}

    ClassA& operator*()
    {
        return *ptr_;  
    }

    ClassA* operator->()
    {
        return ptr_;  
    }

private:
    ClassA* ptr_;
};

int main()
{
    ClassA* objectA = new ClassA(42);

    std::cout << (*objectA).value_ << std::endl;
    std::cout << objectA->value_ << std::endl;

    Ptr ptr(objectA);

    std::cout << (*ptr).value_ << std::endl;
    std::cout << ptr->value_ << std::endl;
}