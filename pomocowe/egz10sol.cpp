#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

int add2(int number){
    return number + 2;
}

int sub2(int number){
    return number - 2;
}

std::function<std::vector<int> (std::vector<int>)> liftToVector(std::function<int(int)> fun){
    return [&](std::vector<int> v) -> std::vector<int>{
        std::vector<int> newV;
        for(auto & elem : v){
            (newV).push_back(fun(elem));
        }
        return newV;
    };
}

int main(){

    auto vadd2 = liftToVector(add2);
    std::vector<int> x = {0,9,4};
    auto v = vadd2(x);

    std::for_each(v.begin(), v.end(), [](const int n) {std::cout<< n << ' ';});

    return 0;
}