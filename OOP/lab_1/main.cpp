#include <iostream>
#include <iomanip>
#include <memory>
#include "Book.h"
#include "Graph.h"

int main() {
    MatrixGraph<int, int> g;
    g.push_vertex(1);
    g.push_vertex(2);
    g.push_vertex(3);
    g.push_vertex(4);
    g.push_vertex(5);
    g.push_vertex(6);
    g.push_edge(5, 1, 4);
    g.push_edge(1, 3, 4);
    g.push_edge(2, 3, 5);
    g.push_edge(1, 4, 6);
    std::cout << std::boolalpha << g.connectivity() << std::endl;
    g.push_edge(20,1, 2);
    std::cout << g.connectivity() << std::endl;
    std::cout << g.length(1, 2)[0] << std::endl;
//    g.push_edge(1,6, 2);
//    std::cout << g.length(1, 2)[0] << std::endl;

    return 0;
}
