//
// Created by Craig Harris on 7/29/24.
//

#include "Matrix.h"
//#include <cmath>

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

void Matrix::Fill(const std::vector<float>& values){
    if (values.size() != this->rows * this->cols){
        throw std::invalid_argument("size of input array doesn't match size of matrix");
    }

    for (int i = 0; i < this->cols * this->rows; ++i){
        this->data[i] = values[i];
    }
}
bool Matrix::operator==(const Matrix& other) const{
    if (this->rows != other.rows || this->cols != other.cols){
        return false;
    }

    for (int i = 0; i < rows * cols; ++i){
        if (std::abs(this->data[i] - other.data[i]) > 10e-5){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const{
    return !(*this == other);
}

Matrix Matrix::operator*(const Matrix& other) const{
    int a_m = this->rows;
    int a_n = this->cols;
    int b_n = other.rows;
    int b_p = other.cols;
    if (a_n != b_n){
        throw std::invalid_argument("Invalid matrix sizes for matrix multiplication");
    }

    Matrix m(a_m, b_p);

    for (int r = 0; r < m.rows; ++r) {
        for (int c = 0; c < m.cols; ++c) {

            float val = 0;
            for (int i = 0; i < a_n; ++i){
                float a_rc = this->data[r * a_m + i];
                float b_cr = other.data[i * b_p + c];
                val += a_rc * b_cr;
            }

            m[r][c] = val;
        }
    }
    return m;
}

Tuple Matrix::operator*(const Tuple& t) const{
    if (this-> rows != 4 and this->cols != 4) {
        throw std::invalid_argument("operation only valid for 4x4 matrices");
    }
    float newTupData[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i){
        newTupData[i] = data[i * 4 + 0] * t.x +
                        data[i * 4 + 1] * t.y +
                        data[i * 4 + 2] * t.z +
                        data[i * 4 + 3] * t.w;
    }
    return Tuple(newTupData[0], newTupData[1], newTupData[2], newTupData[3]);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int r = 0; r < m.rows; ++r) {
        os << "|";
        for (int c = 0; c < m.cols; ++c) {
            os << m.data[r * m.cols + c] << "|";
        }
        os << std::endl;
    }
    return os;
}
