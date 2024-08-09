//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Matrix.h"
#include <vector>

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

//TEST(MatrixTestSuite, MatrixOperandOutOfRange) {
//    Matrix m(3, 3);
//    m[0][0] = 1;
//    EXPECT_EQ(m[0][0], 1);
//    m[5][0] = 1;
//    EXPECT_THROW(m[5][0], std::out_of_range);
//    EXPECT_THROW(m[0][5], std::out_of_range);
//    EXPECT_THROW(m[5][5], std::out_of_range);
//}

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
    Matrix result = a*b;
    EXPECT_EQ(result, c);
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
    EXPECT_EQ(a * b, c);
}

TEST(MatrixTestSuite, MatrixMultiplyByTuple){
    // a_cols needs to equal b_rows
    Matrix A(4, 4);
    A.Fill(std::vector<float> {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1});
    Tuple b(1, 2, 3, 1);
    EXPECT_EQ(A * b, Tuple(18, 24, 33, 1));
}

TEST(MatrixTestSuite, MatrixIdentityMultiplyByMatrix){
    Matrix I = Matrix::Identity(4);
    Matrix A(4, 4);
    A.Fill(std::vector<float> {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1});
    EXPECT_EQ(A * I, A);
}

TEST(MatrixTestSuite, MatrixIdentityMultiplyByTuple){
    Matrix I = Matrix::Identity(4);
    Tuple a(1, 2, 3, 1);
    EXPECT_EQ(I * a, Tuple(1, 2, 3, 1));
}

TEST(MatrixTestSuite, TransposeMatrix44){
    Matrix A(4, 4);
    Matrix C(4, 4);
    A.Fill(std::vector<float> {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8});
    C.Fill(std::vector<float> {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8});
    Matrix AT = Matrix::Transpose(A);
    EXPECT_EQ(AT, C);
}

TEST(MatrixTestSuite, TransposeMatrix22){
    Matrix A(2, 2);
    Matrix C(2, 2);
    A.Fill(std::vector<float> {0, 1, 2, 0});
    C.Fill(std::vector<float> {0, 2, 1, 0});
    Matrix AT = Matrix::Transpose(A);
    EXPECT_EQ(AT, C);
}

TEST(MatrixTestSuite, TransposeMatrixIdentity){
    Matrix A = Matrix::Identity(4);
    Matrix C = Matrix::Identity(4);
    Matrix::Transpose(A);
    EXPECT_EQ(A, C);
}

TEST(MatrixTestSuite, Matrix22Determinant){
    Matrix A(2, 2);
    A.Fill(std::vector<float> {1, 5, -3, 2});
    EXPECT_FLOAT_EQ(Matrix::Determinant(A), 17);
}

TEST(MatrixTestSuite, Matrix33Submatrix22){
    Matrix A(3, 3);
    Matrix C(2, 2);
    A.Fill(std::vector<float> {1, 5, 0, -3, 2, 7, 0, 6, -3});
    C.Fill(std::vector<float> {-3, 2, 0, 6});

    EXPECT_EQ(Matrix::Submatrix(A, 0, 2), C);
}

TEST(MatrixTestSuite, SubmatrixErrors){
    Matrix A(3, 1);
    Matrix B(2, 2);

    EXPECT_THROW(Matrix::Submatrix(A, 0, 0), std::invalid_argument);
    EXPECT_THROW(Matrix::Submatrix(B, 0, 3), std::invalid_argument);
}

TEST(MatrixTestSuite, Minor){
    Matrix A(3, 3);
    A.Fill(std::vector<float> {3, 5, 0, 2, -1, 7, 6, -1, 5});
    Matrix B = Matrix::Submatrix(A, 1, 0);
    EXPECT_FLOAT_EQ(Matrix::Minor(A, 1, 0), Matrix::Determinant(B));
}

TEST(MatrixTestSuite, Cofactor3x3AgainstMinor){
    Matrix A(3, 3);
    A.Fill(std::vector<float> {3, 5, 0, 2, -1, -7, 6, -1, 5});
    EXPECT_FLOAT_EQ(Matrix::Minor(A, 0, 0), -12);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 0), -12);

    EXPECT_FLOAT_EQ(Matrix::Minor(A, 1, 0), 25);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 1, 0), -25);
}

TEST(MatrixTestSuite, Cofactor3x3){
    Matrix A(3, 3);
    A.Fill(std::vector<float> {1, 2, 6, -5, 8, -4, 2, 6, 4});
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 0), 56);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 1), 12);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 2), -46);
    EXPECT_FLOAT_EQ(Matrix::Determinant(A), -196);
}

TEST(MatrixTestSuite, Cofactor4x4){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9});
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 0), 690);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 1), 447);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 2), 210);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 0, 3), 51);
    EXPECT_FLOAT_EQ(Matrix::Determinant(A), -4071);
}

TEST(MatrixTestSuite, MatrixIsInvertible){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {6, 4, 4, 4,
                                       5, 5, 7, 6,
                                       4, -9, 3, -7,
                                       9, 1, 7, -6});
    EXPECT_FLOAT_EQ(Matrix::Determinant(A), -2120);
    EXPECT_TRUE(Matrix::IsInvertible(A));
}

TEST(MatrixTestSuite, MatrixIsNotInvertible){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {-4, 2, -2, -3,
                                       9, 6, 2, 6,
                                       0, -5, 1, -5,
                                       0, 0, 0, 0});
    EXPECT_FLOAT_EQ(Matrix::Determinant(A), 0);
    EXPECT_FALSE(Matrix::IsInvertible(A));
}

TEST(MatrixTestSuite, InverseMatrix){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {-5, 2, 6, -8,
                               1, -5, 1, 8,
                               7, 7, -6, -7,
                               1, -3, 7, 4});
    Matrix B = Matrix::Inverse(A);
    Matrix Correct_Inverse_A(4, 4);
    Correct_Inverse_A.Fill(std::vector<float> {0.21805, 0.45113, 0.24060, -0.04511,
                                       -0.80827, -1.45677, -0.44361, 0.52068,
                                       -0.07895, -0.22368, -0.05263, 0.19737,
                                       -0.52256, -0.81391, -0.30075, 0.30639});

    EXPECT_FLOAT_EQ(Matrix::Determinant(A), 532);
    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 2, 3), -160);
    EXPECT_FLOAT_EQ(B[3][2], -160.f/532.f);

    EXPECT_FLOAT_EQ(Matrix::Cofactor(A, 3, 2), 105);
    EXPECT_FLOAT_EQ(B[2][3], 105.f/532.f);
    EXPECT_EQ(B, Correct_Inverse_A);
}

TEST(MatrixTestSuite, InverseMatrixMult){
    Matrix A(4, 4);
    Matrix B(4, 4);
    A.Fill(std::vector<float> {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1});
    B.Fill(std::vector<float> {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5});
    Matrix C = A * B;
    EXPECT_EQ(C * Matrix::Inverse(B), A);
}

TEST(MatrixTestSuite, CopyMatrix){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1});
    Matrix B = Matrix::copy(A);
    EXPECT_EQ(B, A);
}

TEST(MatrixTestSuite, MatrixTimesInverseIsIdentity){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {6, 4, 4, 4,
                               5, 5, 7, 6,
                               4, -9, 3, -7,
                               9, 1, 7, -6});
    Matrix A_inv = Matrix::Inverse(A);

    Matrix I = Matrix::Identity(4);
    EXPECT_EQ(A_inv * A, I);
    EXPECT_EQ(A * A_inv, I);
}

TEST(MatrixTestSuite, TransposeInverseEqualsInverseTranspose){
    Matrix A(4, 4);
    A.Fill(std::vector<float> {6, 4, 4, 4,
                               5, 5, 7, 6,
                               4, -9, 3, -7,
                               9, 1, 7, -6});

    Matrix A_INV = Matrix::Inverse(A);
    Matrix A_T = Matrix::Transpose(A);
    Matrix A_T_INV = Matrix::Inverse(A_T);
    Matrix A_INV_T = Matrix::Transpose(A_INV);
    EXPECT_EQ(A_T_INV, A_INV_T);
}
