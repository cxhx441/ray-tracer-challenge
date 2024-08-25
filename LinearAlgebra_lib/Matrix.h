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
    std::vector<std::vector<float>> data;
    int rows;
    int cols;
public:
    Matrix(int rows, int cols);

    void Fill(const std::vector<float>& values);
    static Matrix Identity(int n);
    static Matrix Transpose(const Matrix &m);
    static float Determinant(const Matrix &m);
    static Matrix Submatrix(const Matrix &m, int row, int col);
    static Matrix NormalMatrix(const Matrix &m);
    static float Minor(const Matrix &m, int row, int col);
    static float Cofactor(const Matrix &m, int row, int col);
    static bool IsInvertible(const Matrix &m);
    static Matrix Inverse(const Matrix &m);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Tuple operator*(const Tuple& t) const;

    class Row {
    private:
        std::vector<float>& row_data;
        int cols;
    public:
        Row(std::vector<float>& row_data, int cols) ;
        float& operator[](int col);
    };

    Row operator[](int row);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};


#endif //RAYTRACERCHAELLENGE_MATRIX_H
