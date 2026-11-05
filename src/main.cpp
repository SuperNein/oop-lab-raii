#include "matrix.hpp"

#include <iostream>

// Example
int main() {
    Matrix a(2, 2, 1.0); // [[1,1],[1,1]]
    Matrix b(2, 2, 2.0); // [[2,2],[2,2]]

    Matrix s(a);
    s.add(b); // [[3,3],[3,3]]

    Matrix m(a);
    m.mul(b); // [[4,4],[4,4]]

    a.set(0, 0, 5.0);
    a.print(std::cout);

    std::cout << a.rows() << "x" << a.cols() << std::endl;
    
    return 0;
}
