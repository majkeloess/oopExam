#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int add2(int n)
{
    return n + 2;
}

std::function<std::vector<int>(std::vector<int>)> liftToVector(std::function<int(int)> fun)
{
    return [fun](std::vector<int> vec)
    {
        std::vector<int> ret_vec(vec.size());
        for (size_t i = 0; i < ret_vec.size(); i++)
        {
            ret_vec[i] = fun(vec[i]);
        }
        return ret_vec;
    };
}

int main()
{

    auto vadd2 = liftToVector(add2);
    std::vector<int> x = {0, 9, 4};
    auto v = vadd2(x);

    std::for_each(v.begin(), v.end(), [](const int n)
                  { std::cout << n << ' '; });

    return 0;
}
