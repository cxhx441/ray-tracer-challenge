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

    void fill(const std::vector<float>& values);
    static Matrix identity(int n);
    static Matrix transpose(const Matrix &m);
    static float determinant(const Matrix &m);
    static Matrix submatrix(const Matrix &m, int row, int col);
    static Matrix normal_matrix(const Matrix &m);
    static float minor(const Matrix &m, int row, int col);
    static float cofactor(const Matrix &m, int row, int col);
    static bool is_invertible(const Matrix &m);
    static Matrix inverse(const Matrix &m);

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
