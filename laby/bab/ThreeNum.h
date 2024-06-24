#ifndef THREENUM_H
#define THREENUM_H

#include <iostream>
#include <vector>

class ThreeNum
{
private:
  std::vector<double> nums;

public:
  ThreeNum(double x1 = 0, double x2 = 0, double x3 = 0) : nums({x1, x2, x3})
  {
  }

  ThreeNum(const ThreeNum &other) : nums(other.nums) {}

  ThreeNum &operator=(const ThreeNum &other)
  {
    if (this != &other)
    {
      nums = other.nums;
    }
    return *this;
  }

  void setX1(double x1)
  {
    nums[0] = x1;
  }
  void setX2(double x2)
  {
    nums[1] = x2;
  }
  void setX3(double x3)
  {
    nums[2] = x3;
  }
  void setNums(double x1, double x2, double x3)
  {
    nums = {x1, x2, x3};
  }

  double getX1() const { return nums[0]; }
  double getX2() const { return nums[1]; }
  double getX3() const { return nums[2]; }

  ThreeNum operator+(const ThreeNum &other) const
  {
    return ThreeNum(nums[0] + other.nums[0], nums[1] + other.nums[1], nums[2] + other.nums[2]);
  }

  ThreeNum operator*(const ThreeNum &other) const
  {
    return ThreeNum(nums[0] * other.nums[0], nums[1] * other.nums[1], nums[2] * other.nums[2]);
  }

  ThreeNum operator*(double scalar) const
  {
    return ThreeNum(nums[0] * scalar, nums[1] * scalar, nums[2] * scalar);
  }

  ThreeNum &operator+=(const ThreeNum &other)
  {
    *this = *this + other;
    return *this;
  }

  ThreeNum &operator*=(double scalar)
  {
    *this = *this * scalar;
    return *this;
  }

  friend std::istream &operator>>(std::istream &is, ThreeNum &t)
  {
    is >> t.nums[0] >> t.nums[1] >> t.nums[2];

    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const ThreeNum &t)
  {
    os << "[" << t.nums[0] << ", " << t.nums[1] << ", " << t.nums[2] << "]";
    return os;
  }

  double Ave() const
  {
    return 3 / ((1 / nums[0]) + (1 / nums[1]) + (1 / nums[2]));
  }
};

#endif