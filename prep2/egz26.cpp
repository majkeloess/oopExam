#include "wszytskie potrzebne includy"

template</*U1*/>
void my_for_each(/*U2*/){/*U3*/}

int main(){
    using namespace std;
    int c[] = {1,2,3,4,5};

    auto print = /*U4*/;
    auto print_eol = /*U5*/;
    my_for_each(begin(c), end(c), print); print_eol();

    int add_value = 1;
    auto add = /*U6*/;
    my_for_each(begin(c), end(c), add);
    my_for_each(begin(c), end(c), print); print_eol();

    add_value = 10;
    my_for_each(begin(c), end(c), add);
    my_for_each(begin(c), end(c), print); print_eol();
}

//1 2 3 4 5
//2 3 4 5 6
//12 13 14 15 16