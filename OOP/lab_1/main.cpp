#include <iostream>
#include <iomanip>
#include <memory>
#include "Book.h"
#include "Graph.h"

class a {
    std::size_t e;
    char16_t s;

    friend std::ostream &operator<<(std::ostream &out, const a &i);
    friend bool operator<(const a &l, const a &r);

};

std::ostream &operator<<(std::ostream &out, const a &i) {
    out << "{"<<i.e << ", " << i.s <<"}";
    return out;
}

bool operator<(const a &l, const a &r){
    return l.e < r.e;
}

int main() {
//    MatrixGraph<int, int> g;
//    g.push_vertex(1);
//    g.push_vertex(2);
//    g.push_vertex(3);
//    g.push_vertex(4);
//    g.push_vertex(5);
//    g.push_vertex(6);
//    g.push_edge(5, 1, 4);
//    g.push_edge(1, 3, 4);
//    g.push_edge(2, 3, 5);
//    g.push_edge(1, 4, 6);
//    std::cout << std::boolalpha << g.connectivity() << std::endl;
//    g.push_edge(20, 1, 2);
//    g.push_edge(1, 6, 2);
//    std::cout << g.connectivity() << std::endl;
//    std::cout << g.length(1, 2)[0] << std::endl;
//    std::cout << g.length(1, 5)[0] << std::endl;
//    g.push_edge(1, 4, 5);
//    std::cout << g.length(1, 5)[0] << std::endl;
//    std::cout << g.length(4, 2)[0] << std::endl;
//    g.push_edge(1,6, 2);
//    std::cout << g.length(1, 2)[0] << std::endl;
//
//    MatrixGraph<a, a> asd;


    return 0;
}
