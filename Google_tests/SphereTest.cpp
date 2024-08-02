//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Sphere.h"

TEST(SphereTestSuite, RayIntersectsSphereAtTangent){
    Ray r(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<float> xs = Sphere::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0], 5.f);
    EXPECT_EQ(xs[1], 5.f);
}

TEST(SphereTestSuite, RayMissesSphere){
    Ray r(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<float> xs = Sphere::Intersect(s, r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTestSuite, RayOriginateInsideSphere){
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<float> xs = Sphere::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0], -1.f);
    EXPECT_EQ(xs[1], 1.f);
}

TEST(SphereTestSuite, SphereIsBehindRay){
    Ray r(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<float> xs = Sphere::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0], -6.f);
    EXPECT_EQ(xs[1], -4.f);
}
