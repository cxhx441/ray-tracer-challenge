//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Transformation.h"
#include <cmath>

TEST(TransformationTestSuite, MultiplyByTranslationMatrix){
    Matrix T = Transformation::translation(5, -3, 2);
    Tuple p = Tuple::point(-3, 4, 5);
    EXPECT_EQ(T * p, Tuple::point(2, 1, 7));
}

TEST(TransformationTestSuite, MultiplyByInverseOfTranslationMatrix){
    Matrix T = Transformation::translation(5, -3, 2);
    T = Matrix::Inverse(T);
    Tuple p = Tuple::point(-3, 4, 5);
    EXPECT_EQ(T * p, Tuple::point(-8, 7, 3));
}

TEST(TransformationTestSuite, TranslationDoesNotAffectVectors){
    Matrix T = Transformation::translation(5, -3, 2);
    Tuple v = Tuple::vector(-3, 4, 5);
    EXPECT_EQ(T * v, Tuple::vector(-3, 4, 5));
}

TEST(TransformationTestSuite, ScaleMatrixAppliedToPoint){
    Matrix T = Transformation::scaling(2, 3, 4);
    Tuple p = Tuple::point(-4, 6, 8);
    EXPECT_EQ(T * p, Tuple::point(-8, 18, 32));
}

TEST(TransformationTestSuite, ScaleMatrixAppliedToVector){
    Matrix T = Transformation::scaling(2, 3, 4);
    Tuple v = Tuple::vector(-4, 6, 8);
    EXPECT_EQ(T * v, Tuple::vector(-8, 18, 32));
}

TEST(TransformationTestSuite, MultByInverseOfScalingMatrix){
    Matrix T = Transformation::scaling(2, 3, 4);
    T = Matrix::Inverse(T);
    Tuple v = Tuple::vector(-4, 6, 8);
    EXPECT_EQ(T * v, Tuple::vector(-2, 2, 2));
}

TEST(TransformationTestSuite, ReflectionByScalingWithNegative){
    Matrix T = Transformation::scaling(-1, 1, 1);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(-2, 3, 4));
}

TEST(TransformationTestSuite, RotationX_onPoint){
    Tuple p = Tuple::point(0, 1, 0);
    Matrix half_quarter = Transformation::rotation_x(355.f/113.f / 4);
    Matrix full_quarter = Transformation::rotation_x(355.f/113.f / 2);
    EXPECT_EQ(half_quarter * p, Tuple::point(0, sqrt(2) / 2.f, sqrt(2) / 2.f));
    EXPECT_EQ(full_quarter * p, Tuple::point(0, 0, 1));
}

TEST(TransformationTestSuite, RotationX_onPoint_Inverse){
    Tuple p = Tuple::point(0, 1, 0);
    Matrix half_quarter = Transformation::rotation_x(355.f/113.f / 4);
    Matrix inverse_half_quarter = Matrix::Inverse(half_quarter);
    EXPECT_EQ(inverse_half_quarter * p, Tuple::point(0, sqrt(2) / 2.f, -sqrt(2) / 2.f));
}

TEST(TransformationTestSuite, RotationY_onPoint){
    Tuple p = Tuple::point(0, 0, 1);
    Matrix half_quarter = Transformation::rotation_y(355.f/113.f / 4);
    Matrix full_quarter = Transformation::rotation_y(355.f/113.f / 2);
    EXPECT_EQ(half_quarter * p, Tuple::point(sqrt(2) / 2.f, 0, sqrt(2) / 2.f));
    EXPECT_EQ(full_quarter * p, Tuple::point(1, 0, 0));
}

TEST(TransformationTestSuite, RotationY_onPoint_Inverse){
    Tuple p = Tuple::point(0, 0, 1);
    Matrix half_quarter = Transformation::rotation_y(355.f/113.f / 4);
    Matrix full_quarter = Transformation::rotation_y(355.f/113.f / 2);

    Matrix inverse_half_quarter = Matrix::Inverse(half_quarter);
    Matrix inverse_full_quarter = Matrix::Inverse(full_quarter);

    EXPECT_EQ(inverse_half_quarter * p, Tuple::point(-sqrt(2) / 2.f, 0, sqrt(2) / 2.f));
    EXPECT_EQ(inverse_full_quarter * p, Tuple::point(-1, 0, 0));
}

TEST(TransformationTestSuite, RotationZ_onPoint){
    Tuple p = Tuple::point(0, 1, 0);
    Matrix half_quarter = Transformation::rotation_z(355.f/113.f / 4);
    Matrix full_quarter = Transformation::rotation_z(355.f/113.f / 2);
    EXPECT_EQ(half_quarter * p, Tuple::point(-sqrt(2) / 2.f, sqrt(2) / 2.f, 0));
    EXPECT_EQ(full_quarter * p, Tuple::point(-1, 0, 0));
}

TEST(TransformationTestSuite, ShearXy){
    Matrix T = Transformation::shearing(1, 0, 0, 0, 0 ,0);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(5, 3, 4));
}

TEST(TransformationTestSuite, ShearXz){
    Matrix T = Transformation::shearing(0, 1, 0, 0, 0 ,0);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(6, 3, 4));
}

TEST(TransformationTestSuite, ShearYx){
    Matrix T = Transformation::shearing(0, 0, 1, 0, 0 ,0);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(2, 5, 4));
}

TEST(TransformationTestSuite, ShearYz){
    Matrix T = Transformation::shearing(0, 0, 0, 1, 0 ,0);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(2, 7, 4));
}

TEST(TransformationTestSuite, ShearZx){
    Matrix T = Transformation::shearing(0, 0, 0, 0, 1 ,0);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(2, 3, 6));
}

TEST(TransformationTestSuite, ShearZy){
    Matrix T = Transformation::shearing(0, 0, 0, 0, 0 ,1);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(2, 3, 7));
}

TEST(TransformationTestSuite, ShearZy2){
    Matrix T = Transformation::shearing(0, 0, 0, 0, 0 ,2);
    Tuple p = Tuple::point(2, 3, 4);
    EXPECT_EQ(T * p, Tuple::point(2, 3, 10));
}

TEST(TransformationTestSuite, IndividualTransformations){
    Tuple p = Tuple::point(1, 0, 1);
    Matrix A = Transformation::rotation_x(355.f/113.f / 2.f);
    Matrix B = Transformation::scaling(5, 5, 5);
    Matrix C = Transformation::translation(10, 5, 7);

    Tuple p2 = A * p;
    Tuple p3 = B * p2;
    Tuple p4 = C * p3;
    EXPECT_EQ(p4, Tuple::point(15, 0, 7));
}

TEST(TransformationTestSuite, ChainedTransformations){
    Tuple p = Tuple::point(1, 0, 1);
    Matrix A = Transformation::rotation_x(355.f/113.f / 2.f);
    Matrix B = Transformation::scaling(5, 5, 5);
    Matrix C = Transformation::translation(10, 5, 7);

    Matrix T = C * B * A;
    EXPECT_EQ(T * p, Tuple::point(15, 0, 7));

    p = T*p;
    EXPECT_EQ(p, Tuple::point(15, 0, 7));
}
