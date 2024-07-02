#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int add2(int val)
{
    return val +=2;
}


std::function<std::vector<int>(std::vector<int>)> liftToVector(std::function<int(int)> fun)
{
    return [=](std::vector<int>vec){
        std::vector<int> ret_vec;
        for(auto &el: vec)
        {
            ret_vec.push_back(fun(el));
        }

        return ret_vec;
    };
}


int main(){

    auto vadd2 = liftToVector(add2);
    std::vector<int> x = {0,9,4};
    auto v = vadd2(x); // zwrócić wektor muszę tu

    std::for_each(v.begin(), v.end(), [](const int n) {std::cout<< n << ' ';});

    return 0;
}
