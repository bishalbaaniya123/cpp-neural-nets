// Copyright (C) 2021 raodm@miamioh.edu

#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"

#include <cassert>
#include <vector>

Matrix::Matrix(const size_t row, const size_t col, const Val initVal)
    : std::vector<Val>(row * col, initVal) {
    this->col = col;
}

// Operator to write the matrix to a given output stream
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    // Print the number of rows and columns to ease reading
    os << matrix.height() << " " << matrix.width() << '\n';
    // Print each entry to the output stream.
    // for (auto& row : matrix) {
    size_t i = 0;
    for (auto& val : matrix) {
        os << val << " ";
        i++;
        if (i == matrix.col) {
            // Print a new line at the end of each row just to format the
            // output a bit nicely.
            os << '\n';
            i = 0;
        }
    }
    // }
    return os;
}

// Operator to read the matrix to a given input stream.
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    // Temporary variables to load matrix sizes
    int height, width;
    is >> height >> width;
    // Now initialize the destination matrix to ensure it is of the
    // correct dimension.
    matrix = Matrix(height, width);
    // Read each entry from the input stream.
    // for (auto& row : matrix) {
    for (auto& val : matrix) {
        is >> val;
    }
    // }
    return is;
}

Matrix Matrix::dot(const Matrix& rhs) const {
    // Ensure the dimensions are similar.
    assert(col == rhs.height());
    // Setup the result matrix
    const auto mWidth = rhs.col;
    Matrix result(height(), mWidth);
    size_t r = 0;
    // Do the actual matrix multiplication
    for (size_t j = 0; (j < size()); j = j + col) {
        for (size_t k = 0; (k < rhs.col); k++) {
            Val sum = 0;
            for (size_t i = 0; (i < col); i++) {
                sum += (*this)[i + j] * rhs[i * rhs.col + k];
            }
            // Store the result in an appropriate entry
            result[r++] = sum;
        }
    }
    // Return the computed result
    return result;
}

Matrix Matrix::transpose() const {
    // If the matrix is empty, then there is nothing much to do.
    if (empty()) {
        return *this;
    }

    // Create a result matrix that will be the transpose, with width
    // and height flipped.
    Matrix result(width(), height());
    // Now copy the values creating the transpose
    size_t i = 0;
    for (size_t row = 0; (row < width()); row++) {
        for (size_t colm = 0; (colm < result.col); colm++) {
            result[i++] = (*this)[row + col * colm];
        }
    }
    // Return the resulting transpose.
    return result;
}

void Matrix::subtract(const Matrix& rhs) {
    // declare a new matrix to store the difference
    assert(size() == rhs.size());
    assert(col == rhs.col);
    // loop over the elements to multiply
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] = (*this)[i] - rhs[i];
    }
}

Matrix Matrix::mul(const Val e) {
    // declare a new matrix to store the difference
    // loop over the elements to multiply
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] = (*this)[i] * e;
    }
    return *this;
}

#endif
