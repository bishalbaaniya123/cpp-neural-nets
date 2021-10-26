// Copyright (C) 2021 raodm@miamioh.edu

#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"

#include <cassert>
#include <vector>

Matrix::Matrix(const size_t row, const size_t col, const Val initVal)
        : std::vector<std::vector<Val>>(row, std::vector<Val>(col, initVal)) {}

// Operator to write the matrix to a given output stream
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    // Print the number of rows and columns to ease reading
    os << matrix.height() << " " << matrix.width() << '\n';
    // Print each entry to the output stream.
    for (auto& row : matrix) {
        for (auto& val : row) {
            os << val << " ";
        }
        // Print a new line at the end of each row just to format the
        // output a bit nicely.
        os << '\n';
    }
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
    for (auto& row : matrix) {
        for (auto& val : row) {
            is >> val;
        }
    }
    return is;
}

Matrix Matrix::dot(const Matrix& rhs) const {
    // Ensure the dimensions are similar.
    assert(front().size() == rhs.size());
    // Setup the result matrix
    const auto mWidth = rhs.front().size(), width = front().size();
    Matrix result(size(), mWidth);
    // Do the actual matrix multiplication
    for (size_t row = 0; (row < size()); row++) {
        for (size_t col = 0; (col < mWidth); col++) {
            Val sum = 0;
            for (size_t i = 0; (i < width); i++) {
                sum += (*this)[row][i] * rhs[i][col];
            }
            // Store the result in an appropriate entry
            result[row][col] = sum;
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

/*//   START previous code
    for (int row = 0; (row < height()); row++) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }
    // END PREVIOUS CODE*/

    std::array<unsigned long, 2> chunkMatrix =
            getChunkSize(height(), 7);

    for (unsigned long row = 0; row < chunkMatrix[0] - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }

    for (unsigned long row = chunkMatrix[0]; row < chunkMatrix[0] * 2 - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }

    for (unsigned long row = chunkMatrix[0] * 2; row < chunkMatrix[0] * 2 + chunkMatrix[1] - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }
    for (unsigned long row = 0; row < chunkMatrix[0] - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }

    for (unsigned long row = chunkMatrix[0]; row < chunkMatrix[0] * 2 - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }

    for (unsigned long row = chunkMatrix[0]; row < chunkMatrix[0] * 2 - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }

    for (unsigned long row = chunkMatrix[0] * 2; row < chunkMatrix[0] * 2 + chunkMatrix[1] - 1; ++row) {
        for (int col = 0; (col < width()); col++) {
            result[col][row] = (*this)[row][col];
        }
    }
    // Return the resulting transpose.
    return result;
}

std::array<unsigned long, 2> Matrix::getChunkSize(unsigned long loopSize,
                                                  size_t divisions) {
    std::array<unsigned long, 2> arr2{};
    arr2[0] = static_cast<int>(loopSize / divisions);
    arr2[1] = loopSize - arr2[0] * 2;
    return arr2;
}

#endif
