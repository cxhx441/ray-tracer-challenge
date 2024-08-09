//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Intersection.h"

TEST(SphereTestSuite, RayIntersectsSphereAtTangent){
    Ray r(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 5.f);
    EXPECT_EQ(xs[1].t, 5.f);
}

TEST(SphereTestSuite, RayMissesSphere){
    Ray r(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTestSuite, RayOriginateInsideSphere){
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1.f);
    EXPECT_EQ(xs[1].t, 1.f);
}

TEST(SphereTestSuite, SphereIsBehindRay){
    Ray r(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -6.f);
    EXPECT_EQ(xs[1].t, -4.f);
}

TEST(SphereTestSuite, IntersectSetsObjectOnTheIntersection){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].object, &s);
    EXPECT_EQ(xs[1].object, &s);
}

TEST(SphereTestSuite, ASpheresDefaultTransformationIsIdentity){
    Sphere s = Sphere();
    Matrix m = Matrix::Identity(4);
    EXPECT_EQ(s.transformation, m);
}

TEST(SphereTestSuite, ChangeSpheresTransformation){
    Sphere s = Sphere();
    s.transformation = Transformation::translation(2, 3, 4);
    EXPECT_EQ(s.transformation, Transformation::translation(2, 3, 4));
}

TEST(SphereTestSuite, IntersectingAScaledSphereWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    s.transformation = Transformation::scaling(2);
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 3);
    EXPECT_EQ(xs[1].t, 7);
}

TEST(SphereTestSuite, IntersectingATranslatedSphereWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    s.transformation = Transformation::translation(5, 0, 0);
    std::vector<Intersection> xs = Intersection::Intersect(s, r);
    EXPECT_EQ(xs.size(), 0);
}
