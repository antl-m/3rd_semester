#include <iostream>
#include <vector>
#include <algorithm>

struct A{
    int data;
};

struct B{
    unsigned data;
};

bool operator==(A a, B b){
    return a.data == b.data;
}

int main() {
    std::vector<A> a_v;
    for (int i = 0; i < 100; ++i) {
        a_v.push_back(A{i});
    }
    auto it = std::find(a_v.begin(), a_v.end(), B{50});
    std::cout << it->data << std::endl;
    return 0;
}
