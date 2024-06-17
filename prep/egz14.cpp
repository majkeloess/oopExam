#include <iostream>
#include <typeinfo>

 
int main()
{
    typedef B<A> B_A;
    using TypeName = B<B_A>;
    TypeName a = TypeName(TypeName);
    TypeName b(a);
}
