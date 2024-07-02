#include<utility>
#include<iostream>
#include<algorithm>


template <typename T = float>
struct Type_t{
  T _v{};
  Type_t() = default;
  explicit Type_t(T val) : _v{val} {}


  friend std::ostream &operator<<(std::ostream &out, const Type_t &type)
  {
    out << type._v;
    return out;
  }

};

template <typename T>
struct ptr{
  using value_type = T;
  T *m_ptr{};
  ptr() = default;
  explicit ptr(T *ptr) : m_ptr{ptr} {}
  ptr(const ptr &other) = delete;
  ptr(ptr &&other) : m_ptr{other.m_ptr} {
    other.m_ptr = nullptr;
  }

  ptr &operator=(const ptr &other) = delete;

  T &operator*() const 
  {
    return *m_ptr;
  }

  T *operator->() const 
  {
    return m_ptr;
  }

};



using Float_t = Type_t<>;

int main(){
  using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
  Type_ptr t1 { new Type_ptr::value_type{}};
  //Type_ptr t2 = t1; 
  //Type_ptr t2; t2 = t1;
  //Type_ptr t3 = new Type_ptr::value_type();
  (*t1).first = Type_ptr::value_type::first_type{1};
  t1->second = Type_ptr::value_type::second_type{2.5};
  std::cout<< t1->first._v<<" "<<t1->second<<std::endl;

  Type_ptr t2 = std::move(t1);
  //t2->first = 13; 
  //t2->second = 13;
  const Type_ptr t3 = std::move(t2);
  //t3->first = Type_ptr::value_type::first_type{13};
  //t3->second = Type_ptr::value_type::second_type{13}; 

  std::cout<< (*t3).first._v<<" "<<(*t3).second<<std::endl;
  return 0;
}

// 1 2.5
// 1 2.5