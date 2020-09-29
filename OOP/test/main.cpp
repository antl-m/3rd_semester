#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
class TestClass {
public:

    void init(const T &val) {
        bool is_integral = std::is_integral<T>::value;
        return (is_integral ? _init_integral(val) : _init_not_integral(val));
    }

private:


    void _init_integral(const T &val) {
        item = val + 6 * val - 2 * val;
    }

    void _init_not_integral(const T &val){
        for (std::size_t i = 0; i < 5; ++i) {
            vect.push_back(val);
        }
    }

    T item;
    std::vector<T> vect;
};

int main() {

    TestClass<std::vector<int>> tv;
    tv.init({1, 2, 3});

    return 0;
}
