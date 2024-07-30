//
// Created by Craig Harris on 7/29/24.
//

#ifndef RAYTRACERCHAELLENGE_MATRIX_H
#define RAYTRACERCHAELLENGE_MATRIX_H

#include <iostream>


class Matrix {
private:
    float* data;
    int rows;
    int cols;
public:
    Matrix(int rows, int cols);
    ~Matrix();

    class Row {
    private:
        float* row_data;
        int cols;
    public:
        Row(float* row_data, int cols);
        float& operator[](int col);
    };

    Row operator[](int row);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};


#endif //RAYTRACERCHAELLENGE_MATRIX_H
