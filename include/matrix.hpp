#pragma once

#include <cstddef>
#include <stdexcept>
#include <iosfwd>

class Matrix {
public:
    Matrix() = default;
    Matrix(std::size_t rows, std::size_t cols, double init_val = 0.0);
    
    ~Matrix();

    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;

    Matrix& operator=(Matrix other);

    friend void swap(Matrix& first, Matrix& second) noexcept;

    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;

    double get(std::size_t row, std::size_t col) const;
    void set(std::size_t row, std::size_t col, double value);

    void add(const Matrix& other);
    void mul(const Matrix& other);

    bool is_symmetric() const;

    void print(std::ostream& out) const;
    void print() const;

private:
    std::size_t rows_{0}, cols_{0};
    double* data_{nullptr};

    std::size_t index(std::size_t row, std::size_t col) const {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Matrix index out of range");
        }
        return row * cols_ + col;
    }
};
