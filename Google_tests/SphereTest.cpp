//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "primitives/Intersection.h"
#include "primitives/Ray.h"
#include "shapes/Sphere.h"
#include <cmath>

TEST(SphereTestSuite, RayIntersectsSphereAtTangent){
    Ray r(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 5.f);
    EXPECT_EQ(xs[1].t, 5.f);
}

TEST(SphereTestSuite, RayMissesSphere){
    Ray r(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTestSuite, RayOriginateInsideSphere){
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1.f);
    EXPECT_EQ(xs[1].t, 1.f);
}

TEST(SphereTestSuite, SphereIsBehindRay){
    Ray r(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -6.f);
    EXPECT_EQ(xs[1].t, -4.f);
}

TEST(SphereTestSuite, IntersectSetsObjectOnTheIntersection){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].shape, s);
    EXPECT_EQ(xs[1].shape, s);
}

TEST(SphereTestSuite, ASpheresDefaultTransformationIsIdentity){
    auto s = std::make_shared<Sphere>();
    Matrix m = Matrix::identity(4);
    EXPECT_EQ(s->get_transform(), m);
}

TEST(SphereTestSuite, ChangeSpheresTransformation){
    auto s = std::make_shared<Sphere>();
    s->set_transform(Transformation::translation(2, 3, 4));
    EXPECT_EQ(s->get_transform(), Transformation::translation(2, 3, 4));
}

TEST(SphereTestSuite, IntersectingAScaledSphereWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    s->set_transform(Transformation::scaling(2));
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 3);
    EXPECT_EQ(xs[1].t, 7);
}

TEST(SphereTestSuite, IntersectingATranslatedSphereWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    auto s = std::make_shared<Sphere>();
    s->set_transform(Transformation::translation(5, 0, 0));
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTestSuite, NormalOnSphereAtPointOnXAxis){
    auto s = std::make_shared<Sphere>();
    Tuple n = s->normal_at(Tuple::point(1, 0, 0));
    EXPECT_EQ(n, Tuple::vector(1, 0, 0));
}

TEST(SphereTestSuite, NormalOnSphereAtPointOnYAxis){
    auto s = std::make_shared<Sphere>();
    Tuple n = s->normal_at(Tuple::point(0, 1, 0));
    EXPECT_EQ(n, Tuple::vector(0, 1, 0));
}

TEST(SphereTestSuite, NormalOnSphereAtPointOnZAxis) {
    auto s = std::make_shared<Sphere>();
    Tuple n = s->normal_at(Tuple::point(0, 0, 1));
    EXPECT_EQ(n, Tuple::vector(0, 0, 1));
}

TEST(SphereTestSuite, NormalOnSphereAtNonAxialPoint) {
    auto s = std::make_shared<Sphere>();
    Tuple n = s->normal_at(Tuple::point(sqrt(3) / 3.f, sqrt(3) / 3.f, sqrt(3) / 3.f));
    EXPECT_EQ(n, Tuple::vector( sqrt(3) / 3.f, sqrt(3)/ 3.f, sqrt(3) / 3.f));
}

TEST(SphereTestSuite, NormalIsNormalizedVector) {
    auto s = std::make_shared<Sphere>();
    Tuple n = s->normal_at(Tuple::point(sqrt(3) / 3.f, sqrt(3) / 3.f, sqrt(3) / 3.f));
    EXPECT_EQ(n, Tuple::normalized(Tuple::vector(sqrt(3) / 3.f, sqrt(3) / 3.f, sqrt(3) / 3.f)));
}

TEST(SphereTestSuite, ComputeNormalOnTranslatedSphere) {
    auto s = std::make_shared<Sphere>();
    s->set_transform(Transformation::translation(0, 1, 0));
    Tuple n = s->normal_at(Tuple::point(0, 1.70711, -0.70711));
    EXPECT_EQ(n, Tuple::vector( 0, 0.70711, -0.70711));
}

TEST(SphereTestSuite, ComputeNormalOnTransformedSphere) {
    auto s = std::make_shared<Sphere>();
    Matrix scale = Transformation::scaling(1, 0.5, 1);
    Matrix rotate = Transformation::rotation_z(M_PI/5);
    s->set_transform(scale * rotate);
//    Tuple n = s.normal_at(Tuple::point(0, 0.70711, -0.70711));
    Tuple n = s->normal_at(Tuple::point(0, sqrt(2) / 2.f, -sqrt(2) / 2.f));
    EXPECT_EQ(n, Tuple::vector(0, 0.97014, -0.24254));
}

TEST(SphereTestSuite, SphereGetsDefaultMaterial) {
    auto s = std::make_shared<Sphere>();
    EXPECT_EQ(s->material, Material());
}

TEST(SphereTestSuite, SphereMayBeAssignedMaterial) {
    auto s = std::make_shared<Sphere>();
    Material m = Material();
    m.ambient = 1;
    s->material = m;
    EXPECT_EQ(s->material, m);
}

TEST(SphereTestSuite, GlassSphere) {
    Sphere s = Sphere::solid_glass_sphere();
    EXPECT_EQ(s.get_transform(), Matrix::identity(4));
    EXPECT_FLOAT_EQ(s.material.transparency, 1);
    EXPECT_FLOAT_EQ(s.material.refractive_index, 1.5);
}
