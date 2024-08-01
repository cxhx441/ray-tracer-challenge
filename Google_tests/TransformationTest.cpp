//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Transformation.h"

//TEST(TransformationTestSuite, MultiplyByTranslationMatrix){
//    Matrix T = Transformation::translation(5, -3, 2);
//    Tuple p = Tuple::point(-3, 4, 5);
//    EXPECT_EQ(T * p, Tuple::point(2, 1, 7));
//}
//
//TEST(TransformationTestSuite, MultiplyByInverseOfTranslationMatrix){
//    Matrix T = Transformation::translation(5, -3, 2);
//    T = Matrix::Inverse(T);
//    Tuple p = Tuple::point(-3, 4, 5);
//    EXPECT_EQ(T * p, Tuple::point(-8, 7, 3));
//}
//
//TEST(TransformationTestSuite, TranslationDoesNotAffectVectors){
//    Matrix T = Transformation::translation(5, -3, 2);
//    Tuple v = Tuple::vector(-3, 4, 5);
//    EXPECT_EQ(T * v, Tuple::vector(-3, 4, 5));
//}
