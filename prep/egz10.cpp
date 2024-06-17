#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>



int main(){

    auto vadd2 = liftToVector(add2);
    std::vector<int> x = {0,9,4};
    auto v = vadd2(x);

    std::for_each(v.begin(), v.end(), [](const int n) {std::cout<< n << ' ';});

    return 0;
}
