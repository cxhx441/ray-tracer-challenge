//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Ray.h"
#include "Transformation.h"
#include <cmath>

TEST(RayTestSuite, CreateRay){
    Tuple origin = Tuple::point(1, 2, 3);
    Tuple direction = Tuple::vector(4, 5, 6);
    Ray r(origin, direction);
    EXPECT_EQ(r.origin, origin);
    EXPECT_EQ(r.direction, direction);
}

TEST(RayTestSuite, GetRayPosition){
    Ray r(Tuple::point(2, 3, 4), Tuple::vector(1, 0, 0));
    EXPECT_EQ(Ray::position(r, 0), Tuple::point(2, 3, 4));
    EXPECT_EQ(Ray::position(r, 1), Tuple::point(3, 3, 4));
    EXPECT_EQ(Ray::position(r, -1), Tuple::point(1, 3, 4));
    EXPECT_EQ(Ray::position(r, 2.5), Tuple::point(4.5, 3, 4));
}

TEST(RayTestSuite, TranslatingARay){
    Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Matrix m = Transformation::translation(3, 4, 5);
    Ray r2 = Transformation::transform(r, m);
    EXPECT_EQ(r2.origin, Tuple::point(4, 6, 8));
    EXPECT_EQ(r2.direction, Tuple::vector(0, 1, 0));
}

TEST(RayTestSuite, ScalingARay){
    Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Matrix m = Transformation::scaling(2, 3, 4);
    Ray r2 = Transformation::transform(r, m);
    EXPECT_EQ(r2.origin, Tuple::point(2, 6, 12));
    EXPECT_EQ(r2.direction, Tuple::vector(0, 3, 0));
}


