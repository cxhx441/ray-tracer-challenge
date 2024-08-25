//
// Created by Craig Harris on 7/29/24.
//

#include "Matrix.h"
//#include <cmath>

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols) {
    data = std::vector<std::vector<float>> (rows, std::vector<float>(cols, 0));
}

float Matrix::get_data(int r, int c) {
    if (r >= rows || r < 0 || c >= cols || c < 0)
        throw std::out_of_range("Invalid Index!");
    return data[r][c];
}

void Matrix::set_data(int r, int c, float val) {
    if (r >= rows || r < 0 || c >= cols || c < 0)
        throw std::out_of_range("Invalid Index!");
    data[r][c] = val;
}

void Matrix::fill(const std::vector<float>& values){
    if (values.size() != this->rows * this->cols){
        throw std::invalid_argument("size of input array doesn't match size of matrix");
    }

    int i = 0;
    for (int r = 0; r < this->rows; ++r) {
        for (int c = 0; c < this->cols; ++c) {
            this->data[r][c] = values[i];
            ++i;
        }
    }
}

Matrix Matrix::identity(int n){
    Matrix m(n, n);
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < n; ++c){
            if (r == c)
                m.data[r][c] = 1.f;
            else
                m.data[r][c] = 0.f;
        }
    }
    return m;
}

Matrix Matrix::transpose(const Matrix &m) {
    Matrix mT = m;
    for (int r = 0; r < mT.rows; ++r){
        for (int c = r+1; c < mT.cols; ++c) {
            std::swap(mT.data[r][c], mT.data[c][r]);
        }
    }
    return mT;
}

float Matrix::determinant(const Matrix &m) {
    if (m.rows != m.cols)
        throw std::invalid_argument("operation only valid for square matrices");

    if (m.rows == 2 && m.cols == 2)
        return (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]);

    // if not 2x2, recursively find determinant.
    float sub_det = 0;
    for (int c = 0; c < m.cols; ++c){
        sub_det += m.data[0][c] * cofactor(m, 0, c);
    }
    return sub_det;
}

Matrix Matrix::submatrix(const Matrix &m, int row, int col){
    // Returns a matrix with the given row and col removed.
    if (row >= m.rows || col >= m.cols)
        throw std::invalid_argument("given row or col greater than the size of the matrix.");
    if (m.rows == 1 || m.cols == 1)
        throw std::invalid_argument("The matrix already has row or col dimension of 1.");

    std::vector<float> subm_data;
    Matrix subm(m.rows - 1, m.cols - 1);
    for (int r = 0; r < m.rows; ++r){
        for (int c = 0; c < m.cols; ++c) {
            if (r == row || c == col)
                continue;
            subm_data.push_back(m.data[r][c]);
        }
    }
    subm.fill(subm_data);
    return subm;
}

float Matrix::minor(const Matrix &m, int row, int col){
    Matrix subm = Matrix::submatrix(m, row, col);
    return Matrix::determinant(subm);
}

float Matrix::cofactor(const Matrix &m, int row, int col){
    Matrix subm = Matrix::submatrix(m, row, col);
    if ((row + col) % 2 == 0)
        return Matrix::determinant(subm);
    return -1 * Matrix::determinant(subm);
}

bool Matrix::is_invertible(const Matrix &m) {
    return determinant(m) != 0;
}

Matrix Matrix::inverse(const Matrix &m){
    // Compute the inverse Matrix of cofactors.
    //     transpose the matrix of cofactors.
    //     Divide each element by the original matrix's determinant.
    float m_det = determinant(m);
    if (m_det == 0)
        throw std:: invalid_argument("Matrix is Not invertible");

    Matrix inverse_mat(m.rows, m.cols);
    for (int r = 0; r < m.rows; ++r) {
        for (int c = 0; c < m.cols; ++c) {
            // [c][r] instead of [r][c] to handle transposition.
            inverse_mat.data[c][r] = cofactor(m, r, c) / m_det;
        }
    }
    return inverse_mat;
}

Matrix Matrix::normal_matrix(const Matrix &m){
    Matrix n3 = Matrix::submatrix(m, 3, 3);
    Matrix inverse = Matrix::inverse(n3);
    Matrix transpose_inverse = Matrix::transpose(inverse);
    return transpose_inverse;
}

bool Matrix::operator==(const Matrix& other) const{
    if (this->rows != other.rows || this->cols != other.cols){
        return false;
    }

    for (int r = 0; r < this->rows; ++r) {
        for (int c = 0; c < this->cols; ++c) {
            if (std::abs(this->data[r][c] - other.data[r][c]) > 10e-5) {
                return false;
            }
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
                float a_rc = this->data[r][i];
                float b_cr = other.data[i][c];
                val += a_rc * b_cr;
            }

            m.data[r][c] = val;
        }
    }
    return m;
}

Tuple Matrix::operator*(const Tuple& t) const{
    if (this-> rows == 4 and this->cols == 4) {
        float newTupData[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; ++i) {
            newTupData[i] = data[i][0] * t.x +
                            data[i][1] * t.y +
                            data[i][2] * t.z +
                            data[i][3] * t.w;
        }
        return Tuple(newTupData[0], newTupData[1], newTupData[2], newTupData[3]);
    }
    else if (this->rows == 3 and this->cols == 3) {
        float newTupData[3] = {0, 0, 0};
        for (int i = 0; i < 3; ++i) {
            newTupData[i] = data[i][0] * t.x +
                            data[i][1] * t.y +
                            data[i][2] * t.z;
        }
        return Tuple(newTupData[0], newTupData[1], newTupData[2], 0.f);
    }
    else {
        throw std::invalid_argument("operation only valid for 4x4 and 3x3 matrices");
    }
}

//Matrix::Row::Row(std::vector<float>& row_data, int cols) : row_data(row_data), cols(cols) {}
//
//float& Matrix::Row::operator[](int col){
//    if (col < 0 || col >= this->cols) {
//        throw std::out_of_range("col input is out of range");
//    }
//    return row_data[col];
//}
//
//Matrix::Row Matrix::operator[](int row){
//    if (row < 0 || row >= this->rows) {
//        throw std::out_of_range("row input is out of range");
//    }
//    return Row(data[row], cols);
//}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int r = 0; r < m.rows; ++r) {
        os << "|";
        for (int c = 0; c < m.cols; ++c) {
            os << m.data[r][c] << "|";
        }
        os << std::endl;
    }
    return os;
}


