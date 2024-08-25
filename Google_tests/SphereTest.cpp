//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Intersection.h"
#include "Ray.h"
#include "Sphere.h"
#include <cmath>

TEST(SphereTestSuite, RayIntersectsSphereAtTangent){
    Ray r(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 5.f);
    EXPECT_EQ(xs[1].t, 5.f);
}

TEST(SphereTestSuite, RayMissesSphere){
    Ray r(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTestSuite, RayOriginateInsideSphere){
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1.f);
    EXPECT_EQ(xs[1].t, 1.f);
}

TEST(SphereTestSuite, SphereIsBehindRay){
    Ray r(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -6.f);
    EXPECT_EQ(xs[1].t, -4.f);
}

TEST(SphereTestSuite, IntersectSetsObjectOnTheIntersection){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].object, &s);
    EXPECT_EQ(xs[1].object, &s);
}

TEST(SphereTestSuite, ASpheresDefaultTransformationIsIdentity){
    Sphere s = Sphere();
    Matrix m = Matrix::identity(4);
    EXPECT_EQ(s.get_transform(), m);
}

TEST(SphereTestSuite, ChangeSpheresTransformation){
    Sphere s = Sphere();
    s.set_transform(Transformation::translation(2, 3, 4));
    EXPECT_EQ(s.get_transform(), Transformation::translation(2, 3, 4));
}

TEST(SphereTestSuite, IntersectingAScaledSphereWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    s.set_transform(Transformation::scaling(2));
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 3);
    EXPECT_EQ(xs[1].t, 7);
}

TEST(SphereTestSuite, IntersectingATranslatedSphereWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere s = Sphere();
    s.set_transform(Transformation::translation(5, 0, 0));
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTestSuite, NormalOnSphereAtPointOnXAxis){
    Sphere s = Sphere();
    Tuple n = s.normal_at(Tuple::point(1, 0, 0));
    EXPECT_EQ(n, Tuple::vector(1, 0, 0));
}

TEST(SphereTestSuite, NormalOnSphereAtPointOnYAxis){
    Sphere s = Sphere();
    Tuple n = s.normal_at(Tuple::point(0, 1, 0));
    EXPECT_EQ(n, Tuple::vector(0, 1, 0));
}

TEST(SphereTestSuite, NormalOnSphereAtPointOnZAxis) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(Tuple::point(0, 0, 1));
    EXPECT_EQ(n, Tuple::vector(0, 0, 1));
}

TEST(SphereTestSuite, NormalOnSphereAtNonAxialPoint) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(Tuple::point(sqrt(3) / 3.f, sqrt(3) / 3.f, sqrt(3) / 3.f));
    EXPECT_EQ(n, Tuple::vector( sqrt(3) / 3.f, sqrt(3)/ 3.f, sqrt(3) / 3.f));
}

TEST(SphereTestSuite, NormalIsNormalizedVector) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(Tuple::point(sqrt(3) / 3.f, sqrt(3) / 3.f, sqrt(3) / 3.f));
    EXPECT_EQ(n, Tuple::normalized(Tuple::vector(sqrt(3) / 3.f, sqrt(3) / 3.f, sqrt(3) / 3.f)));
}

TEST(SphereTestSuite, ComputeNormalOnTranslatedSphere) {
    Sphere s = Sphere();
    s.set_transform(Transformation::translation(0, 1, 0));
    Tuple n = s.normal_at(Tuple::point(0, 1.70711, -0.70711));
    EXPECT_EQ(n, Tuple::vector( 0, 0.70711, -0.70711));
}

TEST(SphereTestSuite, ComputeNormalOnTransformedSphere) {
    Sphere s = Sphere();
    Matrix scale = Transformation::scaling(1, 0.5, 1);
    Matrix rotate = Transformation::rotation_z(M_PI/5);
    s.set_transform(scale * rotate);
//    Tuple n = s.normal_at(Tuple::point(0, 0.70711, -0.70711));
    Tuple n = s.normal_at(Tuple::point(0, sqrt(2) / 2.f, -sqrt(2) / 2.f));
    EXPECT_EQ(n, Tuple::vector(0, 0.97014, -0.24254));
}

TEST(SphereTestSuite, SphereGetsDefaultMaterial) {
    Sphere s = Sphere();
    EXPECT_EQ(s.material, Material());
}

TEST(SphereTestSuite, SphereMayBeAssignedMaterial) {
    Sphere s = Sphere();
    Material m = Material();
    m.ambient = 1;
    s.material = m;
    EXPECT_EQ(s.material, m);
}
