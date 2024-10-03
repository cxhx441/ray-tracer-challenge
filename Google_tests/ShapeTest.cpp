//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "primitives/Intersection.h"
#include "shapes/TestShape.h"
#include "shapes/Sphere.h"
#include "shapes/Group.h"
#include <cmath>

TEST(ShapeTestSuite, AShapesDefaultTransformationIsIdentity){
    auto s = TestShape::create();
    Matrix m = Matrix::identity(4);
    EXPECT_EQ(s->get_transform(), m);
}

TEST(ShapeTestSuite, ChangeShapesTransformation){
    auto s = TestShape::create();
    s->set_transform( Transformation::translation(2, 3, 4) );
    EXPECT_EQ(s->get_transform(), Transformation::translation(2, 3, 4));
}

TEST(ShapeTestSuite, ShapeGetsDefaultMaterial) {
    auto s = TestShape::create();
    EXPECT_EQ(s->material, Material());
}

TEST(ShapeTestSuite, ShapeMayBeAssignedMaterial) {
    auto s = TestShape::create();
    Material m = Material();
    m.ambient = 1;
    s->material = m;
    EXPECT_EQ(s->material, m);
}

TEST(ShapeTestSuite, IntersectingAScaledShapeWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    auto s = TestShape::create();
    s->set_transform( Transformation::scaling(2) );
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(s->saved_ray.origin, Tuple::point(0, 0, -2.5));
    EXPECT_EQ(s->saved_ray.direction, Tuple::vector(0, 0, 0.5));
}

TEST(ShapeTestSuite, IntersectingATranslatedaShapeWithARay){
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    auto s = TestShape::create();
    s->set_transform( Transformation::translation(5, 0, 0) );
    std::vector<Intersection> xs = s->intersect(r);
    EXPECT_EQ(s->saved_ray.origin, Tuple::point(-5, 0, -5));
    EXPECT_EQ(s->saved_ray.direction, Tuple::vector(0, 0, 1));
}

TEST(ShapeTestSuite, ComputeNormalOnTranslatedShape) {
    auto s = TestShape::create();
    s->set_transform( Transformation::translation(0, 1, 0) );
    Tuple n = s->normal_at(Tuple::point(0, 1.70711, -0.70711));
    EXPECT_EQ(n, Tuple::vector( 0, 0.70711, -0.70711));
}

TEST(ShapeTestSuite, ComputeNormalOnTransformedShape) {
    auto s = TestShape::create();
    Matrix scale = Transformation::scaling(1, 0.5, 1);
    Matrix rotate = Transformation::rotation_z(M_PI/5);
    s->set_transform( scale * rotate );
    Tuple n = s->normal_at(Tuple::point(0, sqrtf(2)/2.f, -sqrtf(2)/2.f));
    EXPECT_EQ(n, Tuple::vector(0, 0.97014, -0.24254));
}

TEST(ShapeTestSuite, ShapeHasNullParent) {
    auto s = TestShape::create();
    EXPECT_EQ(s->parent, nullptr);
}

TEST(ShapeTestSuite, ConvertingAPointFromWorldToObjectSpace) {
    auto g1 = Group::create();
    g1->set_transform(Transformation::rotation_y(M_PI_2));

    auto g2 = Group::create();
    g2->set_transform(Transformation::scaling(2));

    auto s = Sphere::create();
    s->set_transform(Transformation::translation(5, 0, 0));

    g1->add_child(g2);
    g2->add_child(s);
    auto n = s->world_to_object(Tuple::point(-2, 0, -10));
    EXPECT_EQ(n, Tuple::point(0, 0, -1));
}

TEST(ShapeTestSuite, ConvertingANormalFromObjectToWorldSpace) {
    auto g1 = Group::create();
    g1->set_transform(Transformation::rotation_y(M_PI_2));

    auto g2 = Group::create();
    g2->set_transform(Transformation::scaling(1, 2, 3));

    auto s = Sphere::create();
    s->set_transform(Transformation::translation(5, 0, 0));

    g1->add_child(g2);
    g2->add_child(s);
    auto n = s->normal_to_world(Tuple::vector(sqrtf(3)/3, sqrtf(3)/3, sqrtf(3)/3));
    EXPECT_EQ(n, Tuple::vector(0.2857, 0.4286, -0.8571));
}

TEST(ShapeTestSuite, FindingTheNormalOnAChildObject) {
    auto g1 = Group::create();
    g1->set_transform(Transformation::rotation_y(M_PI_2));

    auto g2 = Group::create();
    g2->set_transform(Transformation::scaling(1, 2, 3));

    auto s = Sphere::create();
    s->set_transform(Transformation::translation(5, 0, 0));

    g1->add_child(g2);
    g2->add_child(s);

    auto n = s->normal_at(Tuple::point(1.7321, 1.1547, -5.5774));
    EXPECT_EQ(n, Tuple::vector(0.2857, 0.4286, -0.8571));
}

TEST(ShapeTestSuite, FindNormalOnGroupThrowsError) {
    auto g1 = Group::create();
    g1->set_transform(Transformation::rotation_y(M_PI_2));
    EXPECT_THROW(g1->model_normal_at(Tuple::point(1.7321, 1.1547, -5.5774)), std::runtime_error);
}
