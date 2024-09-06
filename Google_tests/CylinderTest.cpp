//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "primitives/Intersection.h"
#include "primitives/Ray.h"
#include "shapes/Cylinder.h"


TEST(CylinderTestSuite, RayMissesCylinder){
    Cylinder c;

    std::vector<Tuple> origins = {
            Tuple::point(1, 0, 0),
            Tuple::point(0, 0, 0),
            Tuple::point(0, 0, -5),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0, 1, 0),
            Tuple::vector(0, 1, 0),
            Tuple::vector(1, 1, 1),
    };

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], Tuple::normalized(directions[i]));
        std::vector<Intersection> xs = c.intersect(r);
        EXPECT_EQ(xs.size(), 0);
    }
}

TEST(CylinderTestSuite, RayIntersectsCylinder){
    Cylinder c;

    std::vector<Tuple> origins = {
            Tuple::point(1, 0, -5),
            Tuple::point(0, 0, -5),
            Tuple::point(0.5, 0, -5),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0.1, 1, 1),
    };

//    std::vector<float> t0s = { 5, 4, 6.8079991};
//    std::vector<float> t1s = { 5, 6, 7.0887051};
    std::vector<float> t0s = { 5, 4, 6.8080058};
    std::vector<float> t1s = { 5, 6, 7.0886984};

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], Tuple::normalized(directions[i]));
        std::vector<Intersection> xs = c.intersect(r);
        EXPECT_EQ(xs.size(), 2);
        EXPECT_FLOAT_EQ(xs[0].t, t0s[i]);
        EXPECT_FLOAT_EQ(xs[1].t, t1s[i]);
    }
}

TEST(CylinderTestSuite, NormalVectorOnCylinder){
    Cylinder c;

    std::vector<Tuple> points = {
            Tuple::point(1, 0, 0),
            Tuple::point(0, 5, -1),
            Tuple::point(0, -2, 1),
            Tuple::point(-1, 1, 0),
    };
    std::vector<Tuple> normals = {
            Tuple::vector(1, 0, 0),
            Tuple::vector(0, 0, -1),
            Tuple::vector(0, 0, 1),
            Tuple::vector(-1, 0, 0),
    };

    for (int i = 0; i < points.size(); ++i){
        Tuple p = points[i];
        Tuple normal = c.model_normal_at(p);
        EXPECT_EQ(normal, normals[i]);
    }
}

TEST(CylinderTestSuite, DefaultMinMaxHeight){
    Cylinder c;
    EXPECT_EQ(c.minimum, -std::numeric_limits<float>::infinity());
    EXPECT_EQ(c.maximum, std::numeric_limits<float>::infinity());
}

TEST(CylinderTestSuite, IntersectingAConstrainedCylinder){
    Cylinder c;
    c.minimum = 1;
    c.maximum = 2;

    std::vector<Tuple> origins = {
            Tuple::point(0, 1.5, 0),
            Tuple::point(0, 3, -5),
            Tuple::point(0, 0, -5),
            Tuple::point(0, 2, -5),
            Tuple::point(0, 1, -5),
            Tuple::point(0, 1.5, -2),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0.1, 1, 0),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, 1),
    };

    std::vector<int> counts = { 0, 0, 0, 0, 0, 2 };

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], Tuple::normalized(directions[i]));
        std::vector<Intersection> xs = c.intersect(r);
        EXPECT_EQ(xs.size(), counts[i]);
    }
}

TEST(CylinderTestSuite, DefaultClosedValueForCylinder){
    Cylinder c;
    EXPECT_FALSE(c.closed);
}

TEST(CylinderTestSuite, IntersectingTheCapsOfClosedCylinder){
    Cylinder c;
    c.minimum = 1;
    c.maximum = 2;
    c.closed = true;

    std::vector<Tuple> origins = {
            Tuple::point(0, 3, 0),
            Tuple::point(0, 3, -2),
            Tuple::point(0, 4, -2),
            Tuple::point(0, 0, -2),
            Tuple::point(0, -1, -2),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0, -1, 0),
            Tuple::vector(0, -1, 2),
            Tuple::vector(0, -1, 1),
            Tuple::vector(0, 1, 2),
            Tuple::vector(0, 1, 1),
    };

    std::vector<int> counts = {2, 2, 2, 2, 2};

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], Tuple::normalized(directions[i]));
        std::vector<Intersection> xs = c.intersect(r);
        EXPECT_EQ(xs.size(), counts[i]);
    }
}

TEST(CylinderTestSuite, NormalVectorOnClosedCylinder){
    Cylinder c;
    c.minimum = 1;
    c.maximum = 2;
    c.closed = true;

    std::vector<Tuple> points = {
            Tuple::point(0, 1, 0),
            Tuple::point(0.5, 1, 0),
            Tuple::point(0, 1, 0.5),
            Tuple::point(0, 2, 0),
            Tuple::point(0.5, 2, 0),
            Tuple::point(0, 2, 0.5),
    };
    std::vector<Tuple> normals = {
            Tuple::vector(0, -1, 0),
            Tuple::vector(0, -1, 0),
            Tuple::vector(0, -1, 0),
            Tuple::vector(0, 1, 0),
            Tuple::vector(0, 1, 0),
            Tuple::vector(0, 1, 0),
    };

    for (int i = 0; i < points.size(); ++i){
        Tuple p = points[i];
        Tuple normal = c.model_normal_at(p);
        EXPECT_EQ(normal, normals[i]);
    }
}
