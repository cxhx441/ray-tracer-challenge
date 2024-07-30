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
