//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "primitives/Ray.h"
#include "scene/World.h"
#include <cmath>


TEST(IntersectionTestSuite, IntersectionEncapsulatesTandShape){
    auto s = std::make_shared<Sphere>();
    Intersection i(3.5, s);
    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.shape, s);
}

TEST(IntersectionTestSuite, AggregatingIntersections){
    auto s = std::make_shared<Sphere>();
    Intersection i1(1, s);
    Intersection i2(2, s);
    std::vector<Intersection> xs = {i1, i2};
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[1].t, 2);
    EXPECT_EQ(xs[0].shape, s);
    EXPECT_EQ(xs[1].shape, s);
}

TEST(IntersectionTestSuite, HitWhenAllIntersectionsHavePositiveT){
    auto s = std::make_shared<Sphere>();
    Intersection i1(1, s);
    Intersection i2(2, s);
    std::vector<Intersection> xs = {i1, i2};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, i1);
}

TEST(IntersectionTestSuite, HitWhenSomeIntersectionsHaveNegativeT){
    auto s = std::make_shared<Sphere>();
    Intersection i1(-1, s);
    Intersection i2(1, s);
    std::vector<Intersection> xs = {i1, i2};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, i2);
}

TEST(IntersectionTestSuite, HitWhenAllIntersectionsHaveNegativeT){
    auto s = std::make_shared<Sphere>();
    Intersection i1(-2, s);
    Intersection i2(-1, s);
    std::vector<Intersection> xs = {i1, i2};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, std::nullopt);
}

TEST(IntersectionTestSuite, HitIsAlwaysLowestNonNegativeIntersection){
    auto s = std::make_shared<Sphere>();
    Intersection i1(5, s);
    Intersection i2(7, s);
    Intersection i3(-3,s);
    Intersection i4(2, s);
    std::vector<Intersection> xs = {i1, i2, i3, i4};
    std::optional<Intersection> i = Intersection::get_hit(xs);
    EXPECT_EQ(i, i4);
}

TEST(WorldTestSuite, PrecomputeStateOfIntersection) {
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = std::make_shared<Sphere>();
    Intersection i = Intersection(4, shape);
    PreparedComputation comps(i, r, {});
    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, shape);
    EXPECT_EQ(comps.point, Tuple::point(0, 0, -1) );
    EXPECT_EQ(comps.eyev, Tuple::vector(0, 0, -1) );
    EXPECT_EQ(comps.normalv, Tuple::vector(0, 0, -1) );
}

TEST(WorldTestSuite, HitWhenIntersectionOccursOnOutsideOfShape) {
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = std::make_shared<Sphere>();
    Intersection i = Intersection(4, shape);
    PreparedComputation comps(i, r, {});
    EXPECT_FALSE(comps.inside);
}

TEST(WorldTestSuite, HitWhenIntersectionOccursOnInsideOfShape) {
    Ray r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    auto shape = std::make_shared<Sphere>();
    Intersection i = Intersection(1, shape);
    PreparedComputation comps(i, r, {});
    EXPECT_EQ(comps.point, Tuple::point(0, 0, 1) );
    EXPECT_EQ(comps.eyev, Tuple::vector(0, 0, -1) );
    EXPECT_TRUE(comps.inside);
    EXPECT_EQ(comps.normalv, Tuple::vector(0, 0, -1) );
}

TEST(WorldTestSuite, ColorWhenRayMisses) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));
    Color rendered_color = w.color_at(r);
    EXPECT_EQ(rendered_color, Color::black());
}

TEST(WorldTestSuite, ColorWhenRayHits) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Color rendered_color = w.color_at(r);
    EXPECT_EQ(rendered_color, Color(0.38066, 0.47583, 0.2855, 1));
}

TEST(WorldTestSuite, ColorWithIntersectionBehindSphere) {
    World w = World::DefaultWorld();
    std::shared_ptr<Shape> outer = w.shapes[0];
    std::shared_ptr<Shape> inner = w.shapes[1];
    outer->material.ambient = 1;
    inner->material.ambient = 1;
    Ray r = Ray(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));
    Color rendered_color = w.color_at(r);
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
    auto shape = std::make_shared<Sphere>();
    shape->set_transform(Transformation::translation(0, 0, 1));
    Intersection i = Intersection(5, shape);
    PreparedComputation comps(i, r, {});
    EXPECT_LT(comps.over_point.z , -SHADOW_EPSILON/2 ) ;
    EXPECT_GT(comps.point.z , comps.over_point.z);
}

TEST(ShadowTestSuite, PrecomputingTheReflectionVector) {
    auto shape = std::make_shared<Plane>();
    Ray r(Tuple::point(0, 1, -1), Tuple::vector(0, -sqrtf(2)/2 , sqrtf(2)/2));
    Intersection i = Intersection(sqrtf(2), shape);
    PreparedComputation comps(i, r, {});
    EXPECT_EQ(comps.reflectv , Tuple::vector(0, sqrtf(2)/2 , sqrtf(2)/2));
}

TEST(ShadowTestSuite, PrecomputingN1N2AtVariousIntersections) {
    auto A = Sphere::solid_glass();
    auto B = Sphere::solid_glass();
    auto C = Sphere::solid_glass();

    A->set_transform(Transformation::scaling(2));
    B->set_transform(Transformation::translation(0, 0, -0.25));
    C->set_transform(Transformation::translation(0, 0, 0.25));

    A->material.refractive_index = 1.5;
    B->material.refractive_index = 2.0;
    C->material.refractive_index = 2.5;

    Ray r(Tuple::point(0, 0, -4), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = {Intersection(2.00, A),
                                    Intersection(2.75, B),
                                    Intersection(3.25, C),
                                    Intersection(4.75, B),
                                    Intersection(5.25, C),
                                    Intersection(6.00, A) };

    std::vector<PreparedComputation> comps;
    for (auto x : xs){
        comps.push_back(PreparedComputation(x, r, xs));
    }

    EXPECT_FLOAT_EQ(comps[0].n1, 1.0);
    EXPECT_FLOAT_EQ(comps[0].n2, 1.5);

    EXPECT_FLOAT_EQ(comps[1].n1, 1.5);
    EXPECT_FLOAT_EQ(comps[1].n2, 2.0);

    EXPECT_FLOAT_EQ(comps[2].n1, 2.0);
    EXPECT_FLOAT_EQ(comps[2].n2, 2.5);

    EXPECT_FLOAT_EQ(comps[3].n1, 2.5);
    EXPECT_FLOAT_EQ(comps[3].n2, 2.5);

    EXPECT_FLOAT_EQ(comps[4].n1, 2.5);
    EXPECT_FLOAT_EQ(comps[4].n2, 1.5);

    EXPECT_FLOAT_EQ(comps[5].n1, 1.5);
    EXPECT_FLOAT_EQ(comps[5].n2, 1.0);
}

TEST(ShadowTestSuite, UnderPointIsOffsetbelowTheSurface) {
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = Sphere::solid_glass();
    shape->set_transform(Transformation::translation(0, 0, 1));
    Intersection i(5, shape);
    std::vector<Intersection> xs = {i};

    PreparedComputation comps = PreparedComputation(i, r, xs);

    EXPECT_GT(comps.under_point.z, REFRACTION_EPSILON/2.f);
    EXPECT_LT(comps.point.z, comps.under_point.z);
}

TEST(SchlickReflectanceTestSuite, SchlickAppoxUnderTotalInternalReflection) {
    auto shape = Sphere::solid_glass();
    Ray r(Tuple::point(0, 0, sqrtf(2)/2), Tuple::vector(0, 1, 0));
    std::vector<Intersection> xs = {{-sqrtf(2)/2, shape}, {sqrtf(2)/2, shape}};
    PreparedComputation comps = PreparedComputation(xs[1], r, xs);
    float reflectance = World::schlick_reflectance(comps);
    EXPECT_FLOAT_EQ(reflectance, 1);
}

TEST(SchlickReflectanceTestSuite, SchlickAppoxWithPerpendicularViewingAngle) {
    auto shape = Sphere::solid_glass();
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
    std::vector<Intersection> xs = {{-1, shape}, {1, shape}};
    PreparedComputation comps = PreparedComputation(xs[1], r, xs);
    float reflectance = World::schlick_reflectance(comps);
    EXPECT_FLOAT_EQ(reflectance, 0.04);
}

TEST(SchlickReflectanceTestSuite, SchlickAppoxWithSmallAngleAndN2GreaterThanN1) {
    auto shape = Sphere::solid_glass();
    Ray r(Tuple::point(0, 0.99, -2), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = {{1.8589, shape}};
    PreparedComputation comps = PreparedComputation(xs[0], r, xs);
    float reflectance = World::schlick_reflectance(comps);
//    EXPECT_FLOAT_EQ(reflectance, 0.48873);
    EXPECT_FLOAT_EQ(reflectance, 0.4887307);
}

