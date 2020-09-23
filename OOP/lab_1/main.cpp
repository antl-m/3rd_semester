#include <iostream>
#include "test_runner.h"

class A {
public:
    A() {
        static int counter = 0;
        std::cout << ++counter << " objects became" << std::endl;
    }
    ~A(){
        static int counter;
        std::cout << --counter << " objects left" << std::endl;
    }
};

int main() {
    std::cout << -3%2 <<std::endl;
    A a;
    A b;
    return 0;
}
