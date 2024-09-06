//
// Created by Craig Harris on 7/29/24.
//

#include <cmath>
#include "gtest/gtest.h"
#include "primitives/Intersection.h"
#include "primitives/Ray.h"
#include "shapes/Cone.h"

TEST(ConeTestSuite, RayIntersectsCone){
    Cone c;

    std::vector<Tuple> origins = {
            Tuple::point(0, 0, -5),
            Tuple::point(0, 0, -5),
            Tuple::point(1, 1, -5),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0, 0, 1),
            Tuple::vector(1, 1, 1),
            Tuple::vector(-0.5, -1,1),
    };
//    std::vector<float> t0s = {5, 8.66025, 4.55006};
//    std::vector<float> t1s = {5, 8.66025, 49.44994};
    std::vector<float> t0s = {5, 8.6602545, 4.550056};
    std::vector<float> t1s = {5, 8.6602545, 49.44994};

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], Tuple::normalized(directions[i]));
        std::vector<Intersection> xs = c.intersect(r);
        ASSERT_EQ(xs.size(), 2);
        EXPECT_FLOAT_EQ(xs[0].t, t0s[i]);
        EXPECT_FLOAT_EQ(xs[1].t, t1s[i]);
    }
}

TEST(ConeTestSuite, IntersectConeWithARayParallelToOneHalf){
    Cone c;
    Tuple direction = Tuple::normalized(Tuple::vector(0, 1, 1));
    Ray r(Tuple::point(0, 0, -1), direction);
    std::vector<Intersection> xs = c.intersect(r);
    ASSERT_EQ(xs.size(), 1);
//    EXPECT_FLOAT_EQ(xs[0].t, 0.35355);
    EXPECT_FLOAT_EQ(xs[0].t, 0.35355338);
}

TEST(ConeTestSuite, IntersectiongConesCaps){
    Cone c;
    c.minimum = -0.5;
    c.maximum = 0.5;
    c.closed = true;

    std::vector<Tuple> origins = {
            Tuple::point(0, 0, -5),
            Tuple::point(0, 0, -0.25),
            Tuple::point(0, 0, -0.25),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0, 1, 0),
            Tuple::vector(0, 1, 1),
            Tuple::vector(0, 1, 0),
    };

    std::vector<float> counts = {0, 2, 4};

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], Tuple::normalized(directions[i]));
        std::vector<Intersection> xs = c.intersect(r);
        ASSERT_EQ(xs.size(), counts[i]);
    }
}

TEST(ConeTestSuite, NormalVectorOnCone){
    Cone c;

    std::vector<Tuple> points = {
            Tuple::point(0, 0, 0),
            Tuple::point(1, 1, 1),
            Tuple::point(-1, -1, 0),
    };
    std::vector<Tuple> normals = {
            Tuple::vector(0, 0, 0),
            Tuple::vector(1, -sqrtf(2), 1),
            Tuple::vector(-1, 1, 0),
    };

    for (int i = 0; i < points.size(); ++i){
        Tuple p = points[i];
        Tuple normal = c.model_normal_at(p);
        EXPECT_EQ(normal, normals[i]);
    }
}
