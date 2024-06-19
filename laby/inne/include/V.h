#ifndef V_H
#define V_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>
class V
{
private:
  int size;
  int **_tab;

public:
  explicit V(int x) : size(x)
  {
    _tab = new int *[x];
    for (int i = 0; i < size; i++)
    {
      int *temp = new int;
      *temp = 0;
      _tab[i] = temp;
    }
  }

  int &at(int x) const
  {
    return *_tab[x];
  }

  void print(std::string header) const
  {
    std::cout << header << "( ";
    for (int i = 0; i < size; i++)
    {
      std::cout << *_tab[i] << " ";
    }
    std::cout << ")\n";
  }

  V(const V &obj) : size(obj.size)
  {
    _tab = new int *[size];
    for (int i = 0; i < size; i++)
    {
      _tab[i] = new int(*obj._tab[i]);
    }
  }

  V(V &&obj) : size(obj.size)
  {
    _tab = new int *[size];
    for (int i = 0; i < size; i++)
    {
      _tab[i] = new int(*obj._tab[i]);
      *obj._tab[i] = 0;
    }
  }

  static double dot(const V &obj1, const V &obj2)
  {
    int size = 0;
    if (obj1.size == obj2.size)
    {
      size = obj1.size;
    }
    else
    {
      std::cout << "Error, vectors of different dimensions!" << std::endl;
      return 1;
    }
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
      sum += *obj1._tab[i] * *obj2._tab[i];
    }

    return sum;
  }

  double norm() const
  {
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
      sum += *_tab[i] * *_tab[i];
    }
    return sqrt(sum);
  }

  operator double() const
  {
    return this->norm();
  }

  static V sum(const V &obj1, const V &obj2)
  {
    V temp = V(obj1.size);
    for (int i = 0; i < temp.size; i++)
    {
      temp.at(i) = *obj1._tab[i] + *obj2._tab[i];
    }
    return temp;
  }

  static V sum(const V &obj, int x)
  {
    for (int i = 0; i < obj.size; i++)
    {
      *obj._tab[i] += x;
    }
    return obj;
  }

  ~V()
  {
    for (int i = 0; i < size; i++)
    {
      delete _tab[i];
    }
    delete _tab;
  }
};

#endif