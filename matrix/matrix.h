#pragma once
#include <vector>

class Matrix {
public:
    Matrix(int rows, int cols)
        : rows_(rows)
        , cols_(cols)
        , matrix_(rows, std::vector<double>(cols, 0.0)) {}

    explicit Matrix(int square)
        : rows_(square)
        , cols_(square)
        , matrix_(square, std::vector<double>(square, 0.0)) {}

    explicit Matrix(std::vector<std::vector<double>> matrix)
        : rows_(matrix.size())
        , cols_(matrix[0].size())
        , matrix_(matrix) {}

    int Rows() const {
        return rows_;
    }

    int Columns() const {
        return cols_;
    }

    double &operator()(int row, int col) {
        return matrix_[row][col];
    }

    const double &operator()(int row, int col) const {
        return matrix_[row][col];
    }

    Matrix &operator+=(const Matrix &other) {
        if (cols_ != other.Columns() || rows_ != other.Rows()) {
            throw std::invalid_argument("Matrix size mismatch");
        }
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] += other.matrix_[i][j];
            }
        }
        return *this;
    }

    Matrix &operator-=(const Matrix &other) {
        if (cols_ != other.Columns() || rows_ != other.Rows()) {
            throw std::invalid_argument("Matrix size mismatch");
        }
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] -= other.matrix_[i][j];
            }
        }
        return *this;
    }

    Matrix operator*(const Matrix &other) const {
        Matrix result(rows_, other.Columns());
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.Columns(); ++j) {
                for (int k = 0; k < cols_; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }



private:
    int rows_;
    int cols_;
    std::vector<std::vector<double>> matrix_;
};

inline Matrix operator+(Matrix lhs, const Matrix &rhs) {
    return lhs += rhs;
}

inline Matrix operator-(Matrix lhs, const Matrix &rhs) {
    return lhs -= rhs;
}

inline Matrix operator*=(Matrix lhs, const Matrix &rhs) {
    lhs = lhs * rhs;
    return lhs;
}

inline Matrix Transpose(const Matrix &matrix) {
    Matrix result(matrix.Columns(), matrix.Rows());

    for (int i = 0; i < matrix.Rows(); ++i) {
        for (int j = 0; j < matrix.Columns(); ++j) {
            result(j, i) = matrix(i, j);
        }
    }
    return result;
}

inline Matrix Identity(int size) {
    Matrix result(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                result(i, j) = 1.0;
            }
        }
    }
    return result;
}