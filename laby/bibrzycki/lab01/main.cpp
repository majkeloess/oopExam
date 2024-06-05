#include <iostream>

class Vector
{
private:
  int *m_vec{new int[3]};

public:
  Vector() = default;
  Vector(int x, int y, int z)
  {
    m_vec[0] = x;
    m_vec[1] = y;
    m_vec[2] = z;
  }

  Vector(const Vector &v)
  {
    m_vec = new int[3];
    m_vec[0] = v.m_vec[0];
    m_vec[1] = v.m_vec[1];
    m_vec[2] = v.m_vec[2];
  }

  ~Vector()
  {
    delete[] m_vec;
    m_vec = nullptr;
  }

  int &operator[](int index)
  {
    return m_vec[index];
  }

  Vector operator-() const
  {
    Vector retVec{};
    retVec.m_vec[0] = -m_vec[0];
    retVec.m_vec[1] = -m_vec[1];
    retVec.m_vec[2] = -m_vec[2];
    return retVec;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector &v);
  friend Vector operator+(const Vector &v1, const Vector &v2);
  friend Vector operator-(const Vector &v1, const Vector &v2);
  friend int operator*(const Vector &v1, const Vector &v2);
  friend Vector operator*(const Vector &v, int number);
  friend Vector operator*(int number, const Vector &v);
  friend bool operator==(const Vector &v1, const Vector &v2);
  friend bool operator!=(const Vector &v1, const Vector &v2);
};

Vector operator+(const Vector &v1, const Vector &v2)
{
  Vector retVec{};
  retVec.m_vec[0] = v1.m_vec[0] + v2.m_vec[0];
  retVec.m_vec[1] = v1.m_vec[1] + v2.m_vec[1];
  retVec.m_vec[2] = v1.m_vec[2] + v2.m_vec[2];

  return retVec;
}

Vector operator-(const Vector &v1, const Vector &v2)
{
  Vector retVec{};
  retVec.m_vec[0] = v1.m_vec[0] - v2.m_vec[0];
  retVec.m_vec[1] = v1.m_vec[1] - v2.m_vec[1];
  retVec.m_vec[2] = v1.m_vec[2] - v2.m_vec[2];

  return retVec;
}

int operator*(const Vector &v1, const Vector &v2)
{
  int scalar = v1.m_vec[0] * v2.m_vec[0] + v1.m_vec[1] * v2.m_vec[1] + v1.m_vec[2] * v2.m_vec[2];
  return scalar;
}

Vector operator*(const Vector &v, int number)
{
  Vector retVec{};
  retVec.m_vec[0] = v.m_vec[0] * number;
  retVec.m_vec[1] = v.m_vec[1] * number;
  retVec.m_vec[2] = v.m_vec[2] * number;

  return retVec;
}

Vector operator*(int number, const Vector &v)
{
  Vector retVec{};
  retVec.m_vec[0] = v.m_vec[0] * number;
  retVec.m_vec[1] = v.m_vec[1] * number;
  retVec.m_vec[2] = v.m_vec[2] * number;

  return retVec;
}

bool operator==(const Vector &v1, const Vector &v2)
{
  return v1.m_vec[0] == v2.m_vec[0] && v1.m_vec[1] == v2.m_vec[1] && v1.m_vec[2] == v2.m_vec[2];
}

bool operator!=(const Vector &v1, const Vector &v2)
{
  return !(v1 == v2);
}

std::ostream &operator<<(std::ostream &out, const Vector &v)
{
  out << "[" << v.m_vec[0] << v.m_vec[1] << v.m_vec[2] << "]" << std::endl;
  return out;
}

int main()
{

  Vector v1 = {2, 2, 2};
  Vector v2 = {1, 1, 1};

  std::cout << v1 + v2 << std::endl;
  std::cout << v1 - v2 << std::endl;
  std::cout << v1 * 2 << std::endl;
  std::cout << 2 * v1 << std::endl;
  std::cout << v1 * v2 << std::endl;
  std::cout << (v1[0] == ((v2[0]) = (2 * v2[0]))) << std::endl;
  std::cout << (v1[0] != ((v2[0]) = (2 * v2[0]))) << std::endl;
  std::cout << -v2 << std::endl;
}