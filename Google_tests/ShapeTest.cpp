//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "primitives/Intersection.h"
#include "shapes/TestShape.h"
#include <cmath>

TEST(ShapeTestSuite, AShapesDefaultTransformationIsIdentity){
    TestShape s = TestShape();
    Matrix m = Matrix::identity(4);
    EXPECT_EQ(s.get_transform(), m);
}

TEST(ShapeTestSuite, ChangeShapesTransformation){
    TestShape s = TestShape();
    s.set_transform( Transformation::translation(2, 3, 4) );
    EXPECT_EQ(s.get_transform(), Transformation::translation(2, 3, 4));
}

TEST(ShapeTestSuite, ShapeGetsDefaultMaterial) {
    TestShape s = TestShape();
    EXPECT_EQ(s.material, Material());
}

TEST(ShapeTestSuite, ShapeMayBeAssignedMaterial) {
    TestShape s = TestShape();
    Material m = Material();
    m.ambient = 1;
    s.material = m;
    EXPECT_EQ(s.material, m);
}

TEST(ShapeTestSuite, IntersectingAScaledShapeWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    TestShape s = TestShape();
    s.set_transform( Transformation::scaling(2) );
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(s.saved_ray.origin, Tuple::point(0, 0, -2.5));
    EXPECT_EQ(s.saved_ray.direction, Tuple::vector(0, 0, 0.5));
}

TEST(ShapeTestSuite, IntersectingATranslatedaShapeWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    TestShape s = TestShape();
    s.set_transform( Transformation::translation(5, 0, 0) );
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_EQ(s.saved_ray.origin, Tuple::point(-5, 0, -5));
    EXPECT_EQ(s.saved_ray.direction, Tuple::vector(0, 0, 1));
}

TEST(ShapeTestSuite, ComputeNormalOnTranslatedShape) {
    TestShape s = TestShape();
    s.set_transform( Transformation::translation(0, 1, 0) );
    Tuple n = s.normal_at(Tuple::point(0, 1.70711, -0.70711));
    EXPECT_EQ(n, Tuple::vector( 0, 0.70711, -0.70711));
}

TEST(ShapeTestSuite, ComputeNormalOnTransformedShape) {
    TestShape s = TestShape();
    Matrix scale = Transformation::scaling(1, 0.5, 1);
    Matrix rotate = Transformation::rotation_z(M_PI/5);
    s.set_transform( scale * rotate );
    Tuple n = s.normal_at(Tuple::point(0, sqrtf(2)/2.f, -sqrtf(2)/2.f));
    EXPECT_EQ(n, Tuple::vector(0, 0.97014, -0.24254));
}

//TEST(ShapeTestSuite, ASphereIsAShape) {
//    Sphere s = Sphere();
//    EXPECT_EQ(s.material, m);
//}
