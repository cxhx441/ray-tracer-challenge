//
// Created by Craig Harris on 7/27/24.
//

#include "gtest/gtest.h"
#include "shapes/Group.h"
#include "shapes/Sphere.h"
#include "shapes/TestShape.h"


TEST(GroupTestSuite, CreateGroup) {
    auto g = Group::create();
    EXPECT_EQ(g->get_transform(), Matrix::identity(4));
    EXPECT_EQ(g->children.size(), 0);
}

TEST(GroupTestSuite, AddChildToGroup) {
    auto g = Group::create();
    auto s = TestShape::create();
    g->add_child(s);

    ASSERT_EQ(g->children.size(), 1);
    EXPECT_EQ(g->children[0], s);
    EXPECT_EQ(s->parent, g);
}

TEST(GroupTestSuite, IntersectionOnEmptyGroupIsEmpty) {
    auto g = Group::create();
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    auto xs = g->model_intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(GroupTestSuite, IntersectionOnNonEmptyGroup) {
    auto g = Group::create();
    auto s1 = Sphere::create();
    auto s2 = Sphere::create();
    s2->set_transform(Transformation::translation(0, 0,-3));
    auto s3 = Sphere::create();
    s3->set_transform(Transformation::translation(5, 0,0));
    g->add_child(s1);
    g->add_child(s2);
    g->add_child(s3);

    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto xs = g->model_intersect(r);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].shape, s2);
    EXPECT_EQ(xs[1].shape, s2);
    EXPECT_EQ(xs[2].shape, s1);
    EXPECT_EQ(xs[3].shape, s1);
}

TEST(GroupTestSuite, IntersectingATrnsformedGroup) {
    auto g = Group::create();
    g->set_transform(Transformation::scaling(2));
    auto s = Sphere::create();
    s->set_transform(Transformation::translation(5, 0, 0));
    g->add_child(s);

    Ray r(Tuple::point(10, 0, -10), Tuple::vector(0, 0, 1));
    auto xs = g->model_intersect(r);
    ASSERT_EQ(xs.size(), 2);
}

