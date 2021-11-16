// Copyright (C) 2021 raodm@miamioh.edu

#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <cassert>
#include <vector>
#include <array>
#include "Matrix.h"

Matrix::Matrix(const size_t row, const size_t col, const Val initVal)
        : std::vector<Val>(row * col, initVal) {
    this->col = col;
}

// Operator to write the matrix to a given output stream
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    // Print the number of rows and columns to ease reading
    os << matrix.height() << " " << matrix.width() << '\n';
    // Print each entry to the output stream.
    size_t i = 0;
    // instead of two for loops, only one for loop is needed
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
    return os;
}

// Operator to read the matrix to a given input stream.
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    // Temporary variables to load matrix sizes
    size_t height, width;
    is >> height >> width;
    // Now initialize the destination matrix to ensure it is of the
    // correct dimension.
    matrix = Matrix(height, width);
    // Read each entry from the input stream.
    for (auto& val : matrix) {
        is >> val;
    }
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
    //   START previous code
/*    size_t i = 0;
    for (size_t row = 0; (row < width()); row++) {
        for (size_t colVal = 0; (colVal < result.col); colVal++) {
            result[i++] = (*this)[row + col * colVal];
        }
    }*/
    // END PREVIOUS CODE

    std::array<size_t, 2> chunkMatrix =
            getChunkSize(width(), 3);

    size_t i = 0;
    for (size_t row = 0; (row < chunkMatrix[0]); row++) {
        for (size_t colVal = 0; (colVal < result.col); colVal++) {
            result[i++] = (*this)[row + col * colVal];
        }
    }
    for (size_t row = chunkMatrix[0]; (row < chunkMatrix[0] * 2); row++) {
        for (size_t colVal = 0; (colVal < result.col); colVal++) {
            result[i++] = (*this)[row + col * colVal];
        }
    }
    for (size_t row = chunkMatrix[0] * 2;
         (row < chunkMatrix[0] * 2 + chunkMatrix[1]); row++) {
        for (size_t colVal = 0; (colVal < result.col); colVal++) {
            result[i++] = (*this)[row + col * colVal];
        }
    }
    // Return the resulting transpose.
    return result;
}

/**
 * Perform subtraction between two matrices using pass by reference
 *
 * @param rhs The right hand side matrix
 */
void Matrix::subtract(const Matrix& rhs) {
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] = (*this)[i] - rhs[i];
    }
}

/**
 * Matrix multiplication by a constant
 * @param c The constant
 */
Matrix Matrix::mul(const Val c) {
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] = (*this)[i] * c;
    }
    return *this;
}


#endif
