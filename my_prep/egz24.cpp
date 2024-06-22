#include <iostream>
#include <string>
#include <vector>
#include <iterator>
class Person
{
private:
  std::string m_fname{};
  std::string m_lname{};

public:
  Person(const std::string &fname, const std::string &lname) : m_fname{fname}, m_lname{lname} {}

  const std::string &getFname() const
  {
    return m_fname;
  }
  const std::string &getLname() const
  {
    return m_lname;
  }

  friend std::ostream &operator<<(std::ostream &out, const Person &per);
};

std::ostream &operator<<(std::ostream &out, const Person &per)
{
  out << per.m_lname << " " << per.m_fname;
  return out;
}

class Container
{
private:
  std::vector<Person> m_vec{};

public:
  void insert(const Person &per)
  {

    bool exist = false;

    for (size_t i = 0; i < m_vec.size(); i++)
    {
      if ((m_vec[i].getLname() == per.getLname()) && (m_vec[i].getFname() == per.getFname()))
      {
        exist = true;
      }
    }
    if (!exist)
      m_vec.insert(m_vec.begin(), per);
  }

  std::vector<Person>::iterator begin()
  {
    return m_vec.begin();
  }

  std::vector<Person>::iterator end()
  {
    return m_vec.end();
  };
};

int main()
{
  typedef Container kontener_typ;
  kontener_typ c;
  c.insert(Person("Nowak", "Jan"));
  c.insert(Person("Nowak", "Adam"));
  c.insert(Person("Kowalski", "Jan"));
  c.insert(Person("Nowak", "Adam"));
  c.insert(Person("Iksinski", "Adam"));
  std::copy(c.begin(), c.end(), std::ostream_iterator<Person>(std::cout, ", "));
  std::cout << std::endl;
}
// Wynika działania:
// Iksinski Adam, Kowalski Jan, Nowak Adam, Nowak Jan,