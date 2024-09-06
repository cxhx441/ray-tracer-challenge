//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "primitives/Intersection.h"
#include "primitives/Ray.h"
#include "shapes/Cube.h"

TEST(CubeTestSuite, RayIntersectsCube){
    /* Create single cube, cast ray at each of its faces to test intersections work correctly. Also, one ray from inside. */
    Cube c;

    // +x , -x, +y, -y, +z, -z, inside
    std::vector<Tuple> origins = {
            Tuple::point(5, 0.5, 0),
            Tuple::point(-5, 0.5, 0),
            Tuple::point(0.5, 5,0),
            Tuple::point(0.5, -5, 0),
            Tuple::point(0.5, 0, 5),
            Tuple::point(0.5, 0, -5),
            Tuple::point(0, 0.5, 0),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(-1, 0, 0),
            Tuple::vector(1, 0, 0),
            Tuple::vector(0, -1, 0),
            Tuple::vector(0, 1, 0),
            Tuple::vector(0, 0, -1),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, 1),
    };
    std::vector<float> t1s = {4, 4, 4, 4, 4, 4, -1};
    std::vector<float> t2s = {6, 6, 6, 6, 6, 6, 1};

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], directions[i]);
        std::vector<Intersection> xs = c.intersect(r);
        EXPECT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].t, t1s[i]);
        EXPECT_EQ(xs[1].t, t2s[i]);
    }
}

TEST(CubeTestSuite, RayMissesCube){
    Cube c;

    std::vector<Tuple> origins = {
            Tuple::point(-2, 0, 0),
            Tuple::point(0, -2, 0),
            Tuple::point(0, 0, -2),
            Tuple::point(2, 0, 2),
            Tuple::point(2, 2, 2),
            Tuple::point(2, 2, 0),
    };
    std::vector<Tuple> directions = {
            Tuple::vector(0.2673, 0.5345, 0.8018),
            Tuple::vector(0.8018, 0.2673, 0.5345),
            Tuple::vector(0.5345, 0.8018, 0.2673),
            Tuple::vector(0, 0, -1),
            Tuple::vector(0, -1, 0),
            Tuple::vector(-1, 0, 0),
    };

    for (int i = 0; i < origins.size(); ++i){
        Ray r(origins[i], directions[i]);
        std::vector<Intersection> xs = c.intersect(r);
        EXPECT_EQ(xs.size(), 0);
    }
}

TEST(CubeTestSuite, NormalAtFaceOfCube){
    Cube c;

    std::vector<Tuple> points = {
            Tuple::point(1, 0.5, -0.8),
            Tuple::point(-1, -0.2, 0.9),
            Tuple::point(-0.4, 1, -0.1),
            Tuple::point(0.3, -1, -0.7),
            Tuple::point(-0.6, 0.3, 1),
            Tuple::point(0.4, 0.4, -1),
            Tuple::point(1, 1, 1),
            Tuple::point(-1, -1, -1),
    };
    std::vector<Tuple> normals = {
            Tuple::vector(1, 0, 0),
            Tuple::vector(-1, 0, 0),
            Tuple::vector(0, 1, 0),
            Tuple::vector(0, -1, 0),
            Tuple::vector(0, 0, 1),
            Tuple::vector(0, 0, -1),
            Tuple::vector(1, 0, 0),
            Tuple::vector(-1, 0, 0),
    };

    for (int i = 0; i < points.size(); ++i){
        Tuple p = points[i];
        Tuple normal = c.model_normal_at(p);
        EXPECT_EQ(normal, normals[i]);
    }
}

