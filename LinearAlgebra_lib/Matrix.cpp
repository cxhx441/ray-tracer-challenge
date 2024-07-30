//
// Created by Craig Harris on 7/29/24.
//

#include "Matrix.h"

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols) {
    data = new float[rows * cols];
}

Matrix::~Matrix() {
    delete[] data;
}

Matrix::Row::Row(float* row_data, int cols) : row_data(row_data), cols(cols) {}

float& Matrix::Row::operator[](int col){
    if (col < 0 || col >= this->cols) {
        throw std::out_of_range("col input is out of range");
    }
    return row_data[col];
}

Matrix::Row Matrix::operator[](int row){
    if (row < 0 || row >= this->rows) {
        throw std::out_of_range("row input is out of range");
    }
    return Row(&data[row * cols], this->cols);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int r = 0; r < m.rows; ++r) {
        os << "|";
        for (int c = 0; c < m.cols; ++c) {
            os << m.data[r * m.cols + c] << "|";
        }
        if (r < m.rows - 1)
            os << std::endl;
    }
    return os;
}
