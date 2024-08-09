//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Intersection.h"


//TEST(IntersectionTestSuite, IntersectionEncapsulatesTandShape){
//    Sphere s = Sphere();
//    Intersection i(3.5, &s);
//    EXPECT_EQ(i.t, 3.5);
//    EXPECT_EQ(i.object, &s);
//}

TEST(IntersectionTestSuite, AggregatingIntersections){
    Sphere s = Sphere();
    Intersection i1(1, &s);
    Intersection i2(2, &s);
    std::vector<Intersection> xs = {i1, i2};
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[1].t, 2);
    EXPECT_EQ(xs[0].object, &s);
    EXPECT_EQ(xs[1].object, &s);
}

TEST(IntersectionTestSuite, HitWhenAllIntersectionsHavePositiveT){
    Sphere s = Sphere();
    Intersection i1(1, &s);
    Intersection i2(2, &s);
    std::vector<Intersection> xs = {i1, i2};
    Intersection* i = Intersection::Hit(xs);
    EXPECT_EQ(*i, i1);
}

TEST(IntersectionTestSuite, HitWhenSomeIntersectionsHaveNegativeT){
    Sphere s = Sphere();
    Intersection i1(-1, &s);
    Intersection i2(1, &s);
    std::vector<Intersection> xs = {i1, i2};
    Intersection* i = Intersection::Hit(xs);
    EXPECT_EQ(*i, i2);
}

TEST(IntersectionTestSuite, HitWhenAllIntersectionsHaveNegativeT){
    Sphere s = Sphere();
    Intersection i1(-2, &s);
    Intersection i2(-1, &s);
    std::vector<Intersection> xs = {i1, i2};
    Intersection *i = Intersection::Hit(xs);
    EXPECT_EQ(i, nullptr);
}

TEST(IntersectionTestSuite, HitIsAlwaysLowestNonNegativeIntersection){
    Sphere s = Sphere();
    Intersection i1(5, &s);
    Intersection i2(7, &s);
    Intersection i3(-3, &s);
    Intersection i4(2, &s);
    std::vector<Intersection> xs = {i1, i2, i3, i4};
    Intersection *i = Intersection::Hit(xs);
    EXPECT_EQ(*i, i4);
}
