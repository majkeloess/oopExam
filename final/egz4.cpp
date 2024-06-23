#include <iostream>
#include <cstdlib>
#include <vector>

namespace OOP
{
    template <typename T>
    class Array
    {
    private:
        T *m_arr{};
        size_t m_size{};
        size_t index{};

    public:
        using value_type = T;
        Array(size_t size) : m_size{size}, m_arr{new T[size]} {}

        T &operator[](size_t idx) const
        {
            return m_arr[idx];
        }

        Array &insert(T val)
        {
            m_arr[index] = val;
            index++;
            return *this;
        }

        Array &operator%(T val)
        {
            return insert(val);
        }

        size_t operator~() const
        {
            return index;
        }
    };
};

int main()
{
    typedef ::OOP::Array<int> type;
    type a(rand() % 100 + 10); // nie trzeba seedować żeby program się wykonał

    a.insert('#' - 1).insert('P') % type::value_type('O') % ('-') % ('E') % ('G') % ('Z') % ('1');

    ++a[0];
    for (unsigned i = 0; i != ~a; i++)
    {
        std::cout << static_cast<char>(a[i]) << (i + 1 != ~a ? '_' : '\n');
    }
}
// #_P_O_-_E_G_Z_1