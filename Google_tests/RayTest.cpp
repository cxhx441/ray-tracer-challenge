//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Ray.h"
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
    EXPECT_EQ(Ray::Position(r, 0), Tuple::point(2, 3, 4));
    EXPECT_EQ(Ray::Position(r, 1), Tuple::point(3, 3, 4));
    EXPECT_EQ(Ray::Position(r, -1), Tuple::point(1, 3, 4));
    EXPECT_EQ(Ray::Position(r, 2.5), Tuple::point(4.5, 3, 4));
}


