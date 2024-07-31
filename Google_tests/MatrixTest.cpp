//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Matrix.h"

TEST(MatrixTestSuite, ConstructAndInspectMat4) {
    Matrix m(4, 4);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[0][3] = 4;
    m[1][0] = 5.5;
    m[1][1] = 6.5;
    m[1][2] = 7.5;
    m[1][3] = 8.5;
    m[2][0] = 9;
    m[2][1] = 10;
    m[2][2] = 11;
    m[2][3] = 12;
    m[3][0] = 13.5;
    m[3][1] = 14.5;
    m[3][2] = 15.5;
    m[3][3] = 16.5;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][3], 4);
    EXPECT_EQ(m[1][0], 5.5);
    EXPECT_EQ(m[1][2], 7.5);
    EXPECT_EQ(m[2][2], 11);
    EXPECT_EQ(m[3][0], 13.5);
    EXPECT_EQ(m[3][2], 15.5);
}

TEST(MatrixTestSuite, ConstructAndInspectMat3) {
    Matrix m(3, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 5.5;
    m[1][1] = 6.5;
    m[1][2] = 7.5;
    m[2][0] = 9;
    m[2][1] = 10;
    m[2][2] = 11;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 5.5);
    EXPECT_EQ(m[1][2], 7.5);
    EXPECT_EQ(m[2][2], 11);
    EXPECT_EQ(m[2][0], 9);
}

TEST(MatrixTestSuite, ConstructAndInspectMat2) {
    Matrix m(3, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 5.5;
    m[1][1] = 6.5;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][0], 5.5);
}

TEST(MatrixTestSuite, MatrixOperandOutOfRange) {
    Matrix m(3, 3);
    m[0][0] = 1;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_THROW(m[5][0], std::out_of_range);
    EXPECT_THROW(m[0][5], std::out_of_range);
    EXPECT_THROW(m[5][5], std::out_of_range);
}

TEST(MatrixTestSuite, MatrixEquality){
    Matrix a(4, 4);
    Matrix b(4, 4);
    float n = 1.f/3;
    for (int r = 0; r < 4; ++r){
        for (int c = 0; c < 4; ++c) {
            a[r][c] = n;
            b[r][c] = n;
            ++n;
        }
    }
    EXPECT_EQ(a, b);
}

TEST(MatrixTestSuite, MatrixInequality){
    Matrix a(4, 4);
    Matrix b(4, 4);
    float n = 1.f/3;
    for (int r = 0; r < 4; ++r){
        for (int c = 0; c < 4; ++c) {
            a[r][c] = n;
            b[r][c] = n;
            ++n;
        }
    }
    a[2][2] = -10.2;
    EXPECT_NE(a, b);
}

TEST(MatrixTestSuite, Matrix44Multiply){
    Matrix a(4, 4);
    Matrix b(4, 4);
    Matrix c(4, 4);
    std::vector<float> a_vals = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<float> b_vals = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
    std::vector<float> c_vals = {20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42};
    a.Fill(a_vals);
    b.Fill(b_vals);
    c.Fill(c_vals);
    Matrix check = a*b;
    EXPECT_EQ(a * b, c);
}

TEST(MatrixTestSuite, MatrixBadMultiply){
    // a_cols needs to equal b_rows
    Matrix a(4, 1);
    Matrix b(2, 4);
    EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(MatrixTestSuite, MatrixMNMultiply){
    // a_cols needs to equal b_rows
    Matrix a(2, 2);
    Matrix b(2, 1);
    Matrix c(2, 1);
    a.Fill(std::vector<float> {1, 2, 3, 4});
    b.Fill(std::vector<float> {10, 20});
    c.Fill(std::vector<float> {50, 110});
//    Matrix cc = a*b;
    EXPECT_EQ(a * b, c);
}

TEST(MatrixTestSuite, MatrixMultiplyByTuple){
    // a_cols needs to equal b_rows
    Matrix A(4, 4);
    A.Fill(std::vector<float> {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1});
    Tuple b(1, 2, 3, 1);
//    Tuple cc = A*b;
    EXPECT_EQ(A * b, Tuple(18, 24, 33, 1));
}
