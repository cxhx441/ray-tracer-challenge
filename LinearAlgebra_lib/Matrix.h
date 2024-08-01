//
// Created by Craig Harris on 7/29/24.
//

#ifndef RAYTRACERCHAELLENGE_MATRIX_H
#define RAYTRACERCHAELLENGE_MATRIX_H

#include "Tuple.h"
#include <iostream>
#include <vector>

class Matrix {
private:
    float* data;
    int rows;
    int cols;
public:
    Matrix(int rows, int cols);
    ~Matrix();
    void Fill(const std::vector<float>& values);
    static Matrix Identity(int n);
    static void Transpose(Matrix& m);
    static float Determinant(Matrix& m);
    static Matrix Submatrix(Matrix& m, int row, int col);
    static float Minor(Matrix& m, int row, int col);
    static float Cofactor(Matrix& m, int row, int col);
    static bool IsInvertible(Matrix& m);
    static Matrix Inverse(Matrix& m);

    class Row {
    private:
        float* row_data;
        int cols;
    public:
        Row(float* row_data, int cols);
        float& operator[](int col);
    };

    Row operator[](int row);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Tuple operator*(const Tuple& t) const;
//    bool operator*(const float& f) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};


#endif //RAYTRACERCHAELLENGE_MATRIX_H
