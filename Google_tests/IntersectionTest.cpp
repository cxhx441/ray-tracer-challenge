//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Ray.h"
#include "World.h"


TEST(IntersectionTestSuite, IntersectionEncapsulatesTandShape){
    Sphere s = Sphere();
    Intersection i(3.5, &s);
    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.object, &s);
}

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
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, i1);
}

TEST(IntersectionTestSuite, HitWhenSomeIntersectionsHaveNegativeT){
    Sphere s = Sphere();
    Intersection i1(-1, &s);
    Intersection i2(1, &s);
    std::vector<Intersection> xs = {i1, i2};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, i2);
}

TEST(IntersectionTestSuite, HitWhenAllIntersectionsHaveNegativeT){
    Sphere s = Sphere();
    Intersection i1(-2, &s);
    Intersection i2(-1, &s);
    std::vector<Intersection> xs = {i1, i2};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, std::nullopt);
}

TEST(IntersectionTestSuite, HitIsAlwaysLowestNonNegativeIntersection){
    Sphere s = Sphere();
    Intersection i1(5, &s);
    Intersection i2(7, &s);
    Intersection i3(-3, &s);
    Intersection i4(2, &s);
    std::vector<Intersection> xs = {i1, i2, i3, i4};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, i4);
}

TEST(WorldTestSuite, PrecomputeStateOfIntersection) {
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere shape = Sphere();
    Intersection i = Intersection(4, &shape);
    PreparedComputation comps(i, r);
    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, &shape);
    EXPECT_EQ(comps.point, Tuple::point(0, 0, -1) );
    EXPECT_EQ(comps.eyev, Tuple::vector(0, 0, -1) );
    EXPECT_EQ(comps.normalv, Tuple::vector(0, 0, -1) );
}

TEST(WorldTestSuite, HitWhenIntersectionOccursOnOutsideOfShape) {
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere shape = Sphere();
    Intersection i = Intersection(4, &shape);
    PreparedComputation comps(i, r);
    EXPECT_FALSE(comps.inside);
}

TEST(WorldTestSuite, HitWhenIntersectionOccursOnInsideOfShape) {
    Ray r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere shape = Sphere();
    Intersection i = Intersection(1, &shape);
    PreparedComputation comps(i, r);
    EXPECT_EQ(comps.point, Tuple::point(0, 0, 1) );
    EXPECT_EQ(comps.eyev, Tuple::vector(0, 0, -1) );
    EXPECT_TRUE(comps.inside);
    EXPECT_EQ(comps.normalv, Tuple::vector(0, 0, -1) );
}

TEST(WorldTestSuite, ColorWhenRayMisses) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));
    Tuple rendered_color = w.color_at(r);
    EXPECT_EQ(rendered_color, Tuple::color(0, 0, 0, 1));
}

TEST(WorldTestSuite, ColorWhenRayHits) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Tuple rendered_color = w.color_at(r);
    EXPECT_EQ(rendered_color, Tuple::color(0.38066, 0.47583, 0.2855, 1));
}

TEST(WorldTestSuite, ColorWithIntersectionBehindSphere) {
    World w = World::DefaultWorld();
    Sphere* outer = &w.spheres[0];
    Sphere* inner = &w.spheres[1];
    outer->material.ambient = 1;
    inner->material.ambient = 1;
    Ray r = Ray(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));
    Tuple rendered_color = w.color_at(r);
    EXPECT_EQ(rendered_color, inner->material.color);
}

TEST(ShadowTestSuite, NoShadowWhenNothingIsCollinearWithPointAndLight) {
    World w = World::DefaultWorld();
    Tuple p = Tuple::point(0, 10, 0);
    EXPECT_FALSE(w.is_shadowed(w.lights[0], p));
}

TEST(ShadowTestSuite, ShadowWhenObjectBetweenPointAndLight) {
    World w = World::DefaultWorld();
    Tuple p = Tuple::point(10, -10, 10);
    EXPECT_TRUE(w.is_shadowed(w.lights[0], p));
}

TEST(ShadowTestSuite, NoShadowWhenObjectObjectBehindLight) {
    World w = World::DefaultWorld();
    Tuple p = Tuple::point(-20, 20, -20);
    EXPECT_FALSE(w.is_shadowed(w.lights[0], p));
}

TEST(ShadowTestSuite, NoShadowWhenObjectIsBehindPoint) {
    World w = World::DefaultWorld();
    Tuple p = Tuple::point(-2, 2, -2);
    EXPECT_FALSE(w.is_shadowed(w.lights[0], p));
}

TEST(ShadowTestSuite, HitShouldOffsetThePoint) {
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1) );
    Sphere shape;
    shape.set_transform(Transformation::translation(0, 0, 1));
    Intersection i = Intersection(5, &shape);
    PreparedComputation comps(i, r);
    EXPECT_LT(comps.over_point.z , -SHADOW_EPSILON/2 ) ;
    EXPECT_GT(comps.point.z , comps.over_point.z);
}
