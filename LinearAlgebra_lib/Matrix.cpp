//
// Created by Craig Harris on 7/29/24.
//

#include "Matrix.h"
//#include <cmath>

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols) {
    data = new float[rows * cols]();
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

Matrix Matrix::Identity(int n){
    Matrix m(n, n);
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < n; ++c){
            if (r == c)
                m[r][c] = 1.f;
            else
                m[r][c] = 0.f;
        }
    }
    return m;
}

Matrix Matrix::Transpose(Matrix &m) {
    Matrix mT = copy(m);
    for (int r = 0; r < mT.rows; ++r){
        for (int c = r+1; c < mT.cols; ++c) {
            std::swap(mT[r][c], mT[c][r]);
        }
    }
    return mT;
}

float Matrix::Determinant(Matrix &m) {
    if (m.rows != m.cols)
        throw std::invalid_argument("operation only valid for square matrices");

    if (m.rows == 2 and m.cols == 2)
        return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);

    // if not 2x2, recursively find determinant.
    float sub_det = 0;
    for (int c = 0; c < m.cols; ++c){
        sub_det += m[0][c] * Cofactor(m, 0, c);
    }
    return sub_det;
}

Matrix Matrix::Submatrix(Matrix& m, int row, int col){
    // Returns a matrix with the given row and col removed.
    if (row >= m.rows || col >= m.cols)
        throw std::invalid_argument("given row or col greater than the size of the matrix.");
    if (m.rows == 1 || m.cols == 1)
        throw std::invalid_argument("The matrix already has row or col dimension of 1.");

    std::vector<float> subm_data;
    Matrix subm(m.rows - 1, m.cols - 1);
    for (int r = 0; r < m.rows; ++r){
        for (int c = 0; c < m.cols; ++c) {
            if (r == row or c == col)
                continue;
            subm_data.push_back(m[r][c]);
//            subm_data.push_back(m.data[r * m.cols + c]);
        }
    }
    subm.Fill(subm_data);
    return subm;
}

float Matrix::Minor(Matrix& m, int row, int col){
    Matrix subm = Matrix::Submatrix(m, row, col);
    return Matrix::Determinant(subm);
}

float Matrix::Cofactor(Matrix& m, int row, int col){
    Matrix subm = Matrix::Submatrix(m, row, col);
    if ((row + col) % 2 == 0)
        return Matrix::Determinant(subm);
    return -1 * Matrix::Determinant(subm);
}

bool Matrix::IsInvertible(Matrix &m) {
    return Determinant(m) != 0;
}

Matrix Matrix::Inverse(Matrix& m){
    // Compute the Inverse Matrix of cofactors.
    //     Transpose the matrix of cofactors.
    //     Divide each element by the original matrix's determinant.
    float m_det = Determinant(m);
    if (m_det == 0)
        throw std:: invalid_argument("Matrix is Not invertible");

    Matrix inverse_mat(m.rows, m.cols);
    for (int r = 0; r < m.rows; ++r) {
        for (int c = 0; c < m.cols; ++c) {
            // [c][r] instead of [r][c] to handle transposition.
            inverse_mat[c][r] = Cofactor(m, r, c) / m_det;
        }
    }
    return inverse_mat;
}

Matrix Matrix::copy(Matrix& m){
    Matrix copy(m.rows, m.cols);
    for (int r = 0; r < m.rows; ++r) {
        for (int c = 0; c < m.cols; ++c) {
            copy[r][c] = m[r][c];
        }
    }
    return copy;
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

