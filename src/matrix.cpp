#include "matrix.hpp"

#include <utility>
#include <iostream>

using std::size_t;

Matrix::Matrix(size_t rows, size_t cols, double init_val)
    : rows_(rows),
      cols_(cols) {
    if (rows == 0 || cols == 0) {
        data_ = nullptr;

        rows = 0;
        cols = 0;

        return;
    }

    data_ = new double[rows * cols]{};

    for (size_t i = 0; i < rows_ * cols_; ++i) {
        data_[i] = init_val;
    }
}

Matrix::~Matrix() {
    delete[] data_;
    data_ = nullptr;

    rows_ = 0;
    cols_ = 0;
}

Matrix::Matrix(const Matrix& other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;

    size_t size = this->rows_ * this->cols_;
    this->data_ = new double[size];

    for (size_t i = 0; i < size; ++i) {
        this->data_[i] = other.data_[i];
    }
}

Matrix::Matrix(Matrix&& other) noexcept {
    swap(*this, other);
}

Matrix& Matrix::operator=(Matrix other) {
    swap(*this, other);
    return *this;
}

void swap(Matrix& first, Matrix& second) noexcept {
    using std::swap;
    
    swap(first.rows_, second.rows_);
    swap(first.cols_, second.cols_);
    swap(first.data_, second.data_);
}

std::size_t Matrix::rows() const noexcept {
    return rows_;
}

std::size_t Matrix::cols() const noexcept {
    return cols_;
}

double Matrix::get(std::size_t row, std::size_t col) const {
    return data_[index(row, col)];
}

void Matrix::set(std::size_t row, std::size_t col, double value) {
    data_[index(row, col)] = value;
}

void Matrix::add(const Matrix& other) {
    if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
        throw std::invalid_argument("Wrong size of matrix");
    }

    for (size_t i = 0; i < cols_ * rows_; ++i) {
        data_[i] += other.data_[i];
    }
}

void Matrix::mul(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Wrong size of matrix");
    }

    Matrix tmp(rows_, other.cols_);

    for (size_t row = 0; row < rows_; ++row) {
        for (size_t col = 0; col < other.cols_; ++col) {
            double val = 0;

            for (size_t i = 0; i < cols_; ++i) {
                val += get(row, i) * other.get(i, col);
            }
            tmp.set(row, col, val);
        }
    }

    *this = std::move(tmp);
}

bool Matrix::is_symmetric() const {
    if (rows_ != cols_) {
        return false;
    }

    if (rows_ <= 1) {
        return true;
    }

    for (size_t row = 0; row < rows_; ++row) {
        for (size_t col = 0; col < cols_; ++col) {
            if (get(row, col) != get(col, row)) {
                return false;
            }
        }
    }

    return true;
}

void Matrix::print(std::ostream& out = std::cout) const {
    out << '[';

    for (size_t row = 0; row < rows_; ++row) {
        out << '[';

        for (size_t col = 0; col < cols_; ++col) {
            out << get(row, col) << ((col + 1 != cols_) ? ", " : "]");
        }

        out << ((row + 1 != rows_) ? ", " : "]\n");
    }
}

void Matrix::print() const {
    print(std::cout);
}
