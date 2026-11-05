#include "matrix.hpp"
#include <iostream>
#include <cstddef>
#include <limits>

void print_menu() {
    std::cout
        << "\n======================\n"
        << "||      Matrix      ||\n"
        << "======================\n"
        << " [1] Create matrix\n"
        << " [2] Print\n"
        << " [3] Get element\n"
        << " [4] Set element\n"
        << " [5] Check is symmetric\n"
        << " [6] Clear matrix\n"
        << " [0] Exit\n"
        << "----------------------\n";
}

int read_int(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "ERROR\n";
    }
}

double read_double(const char* prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "ERROR\n";
    }
}

int main() {
    Matrix m;
    bool running = true;

    print_menu();

    while (running) {
        int command = read_int("\n>> Enter command: ");

        switch (command) {
            case 1: {
                int rows = read_int("Enter rows: ");
                int cols = read_int("Enter cols: ");

                if (rows >= 0 && cols >= 0) {
                    double init_val = read_double("Enter initial value: ");

                    m = Matrix(
                        static_cast<std::size_t>(rows),
                        static_cast<std::size_t>(cols),
                        init_val
                    );

                    std::cout << "Matrix created\n";
                } else {
                    std::cout << "Wrong size\n";
                }
                break;
            }
            case 2: {
                if (m.rows() == 0 || m.cols() == 0) {
                    std::cout << "Matrix is empty\n";
                } else {
                    m.print();
                }
                break;
            }
            case 3: {
                int row = read_int("Enter row: ");
                int col = read_int("Enter col: ");

                if (
                    row >= 0 && col >= 0 &&
                    static_cast<std::size_t>(row) < m.rows() &&
                    static_cast<std::size_t>(col) < m.cols()
                ) {
                    double val = m.get(
                        static_cast<std::size_t>(row),
                        static_cast<std::size_t>(col)
                    );
                    std::cout << "Value: " << val << "\n";
                } else {
                    std::cout << "Index out of range\n";
                }
                break;
            }
            case 4: {
                int row = read_int("Enter row: ");
                int col = read_int("Enter col: ");
                if (
                    row >= 0 && col >= 0 &&
                    static_cast<std::size_t>(row) < m.rows() &&
                    static_cast<std::size_t>(col) < m.cols()
                ) {
                    double val = read_double("Enter new value: ");
                    m.set(
                        static_cast<std::size_t>(row),
                        static_cast<std::size_t>(col),
                        val
                    );

                    std::cout << "Value set\n";
                } else {
                    std::cout << "Index out of range\n";
                }
                break;
            }
            case 5: {
                if (m.rows() == 0 || m.cols() == 0) {
                    std::cout << "Matrix is empty\n";
                } else {
                    std::cout << (
                        m.is_symmetric() 
                        ? "Matrix is symmetric\n" 
                        : "Matrix is not symmetric\n"
                    );
                }
                break;
            }
            case 6: {
                m = Matrix();
                std::cout << "Matrix cleared\n";
                break;
            }
            case 0: {
                running = false;
                std::cout << "Exited\n";
                break;
            }
            default: {
                std::cout << "Unknown command\n";
                break;
            }
        }
    }

    return 0;
}
