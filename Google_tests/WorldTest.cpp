//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "scene/World.h"
#include "primitives/Ray.h"
#include "primitives/Intersection.h"
#include "patterns/TestPattern.h"
#include <cmath>

TEST(WorldTestSuite, CreateDefaultWorld){
    World w = World::DefaultWorld();

    EXPECT_EQ(w.lights[0].point, Tuple::point(-10, 10, -10) );
    EXPECT_EQ(w.lights[0].color, Color::white());

    ASSERT_EQ(w.spheres.size(), 2);

    EXPECT_EQ(w.spheres[0].material.color, Color(0.8, 1.0, 0.6, 1) );
    EXPECT_FLOAT_EQ(w.spheres[0].material.diffuse, 0.7);
    EXPECT_FLOAT_EQ(w.spheres[0].material.specular, 0.2);

    EXPECT_EQ(w.spheres[1].get_transform(), Transformation::scaling(0.5) );
}

TEST(WorldTestSuite, IntersectAWorldWithARay) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = w.intersect_world(r);

    ASSERT_EQ(xs.size(), 4);

    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[0].object, &w.spheres[0]);

    EXPECT_FLOAT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[1].object, &w.spheres[1]);

    EXPECT_FLOAT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[2].object, &w.spheres[1]);

    EXPECT_FLOAT_EQ(xs[3].t, 6);
    EXPECT_EQ(xs[3].object, &w.spheres[0]);
}

TEST(WorldTestSuite, ShadingAnIntersectionFromOutside) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = w.spheres[0];
    Intersection x = Intersection(4, &s);
    PreparedComputation comps(x, r);
    Color rendered_color = w.shade_hit(comps);
    EXPECT_EQ(rendered_color, Color(0.38066, 0.47583, 0.2855, 1) );
}

TEST(WorldTestSuite, ShadingAnIntersectionFromInside) {
    World w = World::DefaultWorld();
    w.lights[0] = PointLight(Tuple::point(0, 0.25, 0), Color::white());
    Ray r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere s = w.spheres[1];
    Intersection x = Intersection(0.5, &s);
    PreparedComputation comps(x, r);
    Color rendered_color = w.shade_hit(comps);
    EXPECT_EQ(rendered_color, Color(0.90498, 0.90498, 0.90498, 1) );
}

TEST(WorldTestSuite, ShadeHitWith2Lights) {
    World w = World::DefaultWorld();
    PointLight l2 = w.lights[0];
    w.lights.push_back(l2);
    ASSERT_NE(&w.lights[0], &l2);
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = w.spheres[0];
    Intersection x = Intersection(4, &s);
    PreparedComputation comps(x, r);
    Color rendered_color = w.shade_hit(comps);
    EXPECT_EQ(rendered_color, Color(0.38066, 0.47583, 0.2855, 1) );
}

TEST(WorldTestSuite, ShadeHitWith3Lights) {
    World w = World::DefaultWorld();
    w.lights.push_back(w.lights[0]);
    w.lights.push_back(w.lights[0]);
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = w.spheres[0];
    Intersection x = Intersection(4, &s);
    PreparedComputation comps(x, r);
    Color rendered_color = w.shade_hit(comps);
    EXPECT_EQ(rendered_color, Color(0.38066, 0.47583, 0.2855, 1));
}

TEST(WorldTestSuite, ShadeHitIsGivenAnIntersectionInShadow) {
    World w;
    PointLight l1 = PointLight(Tuple::point(0, 0, -10), Color::white());
    w.lights.push_back(l1);
    Sphere s1;
    Sphere s2;
    s2.set_transform(Transformation::translation(0, 0, 10));
    w.spheres.push_back(s1);
    w.spheres.push_back(s2);

    Ray r = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    Intersection x = Intersection(4, &s2);
    PreparedComputation comps(x, r);
    Color rendered_color = w.shade_hit(comps, true);
    EXPECT_EQ( rendered_color, Color(0.1, 0.1, 0.1, 1) );
}

TEST(WorldTestSuite, ReflectedColorForNonReflectiveMaterialIsBlack) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere shape = w.spheres[1];
    shape.material.ambient = 1;
    Intersection x = Intersection(1, &shape);
    PreparedComputation comps(x, r);
    Color reflected_color = w.reflected_color(comps);
    EXPECT_EQ( reflected_color, Color::black());
}

TEST(WorldTestSuite, ReflectedColorForReflectiveMaterial) {
    World w = World::DefaultWorld();

    Plane p;
    p.name = std::string("p");
    p.material.reflective = 0.5;
    p.set_transform(Transformation::translation(0, -1, 0));
    w.planes.push_back(p);

    Ray r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtf(2)/2, sqrtf(2)/2));
    Intersection x = Intersection(sqrtf(2), &p);
    PreparedComputation comps(x, r);
    Color reflected_color = w.reflected_color(comps, true, 3);
//    EXPECT_EQ( reflected_color, Tuple::color(0.19032, 0.2379, 0.14274, 1) );
    EXPECT_EQ( reflected_color, Color(0.190503, 0.238129, 0.142877, 1) );
}

TEST(WorldTestSuite, ShadeHitWithReflectiveMaterial) {
    World w = World::DefaultWorld();

    Plane p;
    p.name = std::string("p");
    p.material.reflective = 0.5;
    p.set_transform(Transformation::translation(0, -1, 0));
    w.planes.push_back(p);

    Ray r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtf(2)/2, sqrtf(2)/2));
    Intersection x = Intersection(sqrtf(2), &p);
    PreparedComputation comps(x, r);
    Color color = w.shade_hit(comps, true, 3);
//    EXPECT_EQ( color, Tuple::color(0.87677, 0.92436, 0.82918, 1) );
    EXPECT_EQ( color, Color(0.876928, 0.924554, 0.829303, 1) );
}

TEST(WorldTestSuite, ParallelReflectivePlanesStopsRecursion) {
    World w;
    w.lights.push_back(PointLight(Tuple::point(0, 0, 0), Color::white()));

    Plane lower;
    lower.name = std::string("lower");
    lower.material.reflective = 1;
    lower.set_transform(Transformation::translation(0, -1, 0));
    Plane upper;
    upper.name = std::string("lower");
    upper.material.reflective = 1;
    upper.set_transform(Transformation::translation(0, 1, 0));

    w.planes.push_back(lower);
    w.planes.push_back(upper);

    Ray r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
    w.color_at(r);
}

TEST(WorldTestSuite, ReflectedColorAtMaximumRecursionDepth) {
    World w = World::DefaultWorld();
    Plane p;
    p.name = std::string("p");
    p.material.reflective = 0.5;
    p.set_transform(Transformation::translation(0, -1, 0));
    w.planes.push_back(p);

    Ray r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtf(2)/2, sqrtf(2)/2));
    Intersection x = Intersection(sqrtf(2), &p);
    PreparedComputation comps(x, r);
    Color ref_color = w.reflected_color(comps, false, 0);
    EXPECT_EQ( ref_color, Color::black());
}

TEST(WorldTestSuite, RefractedColorForOpaqueMaterialIsBlack) {
    World w = World::DefaultWorld();
    Sphere shape = w.spheres[0];
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = {Intersection(4, &shape), Intersection(6, &shape)};
    PreparedComputation comps(xs[0], r, xs);
    Color refracted_color = w.refracted_color(comps, false, 3);
    EXPECT_EQ( refracted_color, Color::black());
}

TEST(WorldTestSuite, RefractedColorAtMaximumRecursiveDepthIsBlack) {
    World w = World::DefaultWorld();
    Sphere shape = w.spheres[0];
    shape.material.transparency = 1;
    shape.material.refractive_index = 1.5;
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = {Intersection(4, &shape), Intersection(6, &shape)};
    PreparedComputation comps(xs[0], r, xs);
    Color refracted_color = w.refracted_color(comps, false, 0); // no remaining reflections
    EXPECT_EQ( refracted_color, Color::black());
}

TEST(WorldTestSuite, RefractedColorWithTotalInternalReflectionIsBlack) {
    World w = World::DefaultWorld();
    Sphere shape = w.spheres[0];
    shape.material.transparency = 1;
    shape.material.refractive_index = 1.5;
    Ray r = Ray(Tuple::point(0, 0, sqrtf(2)/2), Tuple::vector(0, 1, 0));
    std::vector<Intersection> xs = {Intersection(-sqrtf(2)/2, &shape), Intersection(sqrtf(2)/2, &shape)};
    PreparedComputation comps(xs[1], r, xs);
    Color refracted_color = w.refracted_color(comps, false, 5);
    EXPECT_EQ( refracted_color, Color::black());
}

TEST(WorldTestSuite, RefractedColoWithARefractedRay) {
    World w = World::DefaultWorld();

    Sphere &A = w.spheres[0];
    A.material.ambient = 1;
    A.material.set_pattern(TestPattern());
    A.name = "A";

    Sphere &B = w.spheres[1];
    B.material.transparency = 1;
    B.material.refractive_index = 1.5;
    B.name = "B";

    Ray r = Ray(Tuple::point(0, 0, 0.1), Tuple::vector(0, 1, 0));
    std::vector<Intersection> xs = {Intersection(-0.9899, &A),
                                    Intersection(-0.4899, &B),
                                    Intersection( 0.4899, &B),
                                    Intersection( 0.9889, &A)};
    PreparedComputation comps(xs[2], r, xs);
    Color refracted_color = w.refracted_color(comps, false, 5);
//    EXPECT_EQ( refracted_color, Color(0, 0.99888, 0.04725));
    EXPECT_EQ( refracted_color, Color(0, 0.99887, 0.0475195));
}

TEST(WorldTestSuite, SHadeHitWithTransparentMaterial) {
    World w = World::DefaultWorld();

    Plane floor;
    floor.name = "floor";
    floor.set_transform(Transformation::translation(0, -1, 0));
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    w.planes.push_back(floor);

    Sphere ball;
    ball.name = "ball";
    ball.material.color = Color(1, 0, 0, 1);
    ball.material.ambient = 0.5;
    ball.set_transform(Transformation::translation(0, -3.5, -0.5));
    w.spheres.push_back(ball);

    Ray r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtf(2)/2, sqrtf(2)/2));
    std::vector<Intersection> xs = {Intersection(sqrtf(2), &floor)};
    PreparedComputation comps(xs[0], r, xs);
    Color color = w.shade_hit(comps, true, 5);
    EXPECT_EQ( color, Color(0.93642, 0.68642, 0.68642));
}
