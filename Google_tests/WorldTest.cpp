//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "World.h"
#include "Ray.h"
#include "Intersection.h"

TEST(WorldTestSuite, CreateDefaultWorld){
    World w = World::DefaultWorld();

    EXPECT_EQ(w.lights[0].position, Tuple::point(-10, 10, -10) );
    EXPECT_EQ(w.lights[0].intensity, Tuple::color(1, 1, 1, 1) );

    ASSERT_EQ(w.objects.size(), 2);

    EXPECT_EQ(w.objects[0].material.color, Tuple::color(0.8, 1.0, 0.6, 1) );
    EXPECT_FLOAT_EQ(w.objects[0].material.diffuse, 0.7);
    EXPECT_FLOAT_EQ(w.objects[0].material.specular, 0.2);

    EXPECT_EQ(w.objects[1].getTransform(), Transformation::scaling(0.5) );
}

TEST(WorldTestSuite, IntersectAWorldWithARay) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = Intersection::IntersectWorld(w, r);

    ASSERT_EQ(xs.size(), 4);

    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[0].object, &w.objects[0]);

    EXPECT_FLOAT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[1].object, &w.objects[1]);

    EXPECT_FLOAT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[2].object, &w.objects[1]);

    EXPECT_FLOAT_EQ(xs[3].t, 6);
    EXPECT_EQ(xs[3].object, &w.objects[0]);
}

TEST(WorldTestSuite, ShadingAnIntersectionFromOutside) {
    World w = World::DefaultWorld();
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = w.objects[0];
    Intersection x = Intersection(4, &s);
    Precompute comps = Intersection::PrepareComputations(x, r);
    Tuple rendered_color = Intersection::ShadeHit(w, comps);
    EXPECT_EQ(rendered_color, Tuple::color(0.38066, 0.47583, 0.2855, 1) );
}

TEST(WorldTestSuite, ShadingAnIntersectionFromInside) {
    World w = World::DefaultWorld();
    w.lights[0] = Light::PointLight(Tuple::point(0, 0.25, 0), Tuple::color(1, 1, 1, 1));
    Ray r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere s = w.objects[1];
    Intersection x = Intersection(0.5, &s);
    Precompute comps = Intersection::PrepareComputations(x, r);
    Tuple rendered_color = Intersection::ShadeHit(w, comps);
    EXPECT_EQ(rendered_color, Tuple::color(0.90498, 0.90498, 0.90498, 1) );
}

TEST(WorldTestSuite, ShadeHitWith2Lights) {
    World w = World::DefaultWorld();
    Light l2 = w.lights[0];
    w.lights.push_back(l2);
    ASSERT_NE(&w.lights[0], &l2);
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = w.objects[0];
    Intersection x = Intersection(4, &s);
    Precompute comps = Intersection::PrepareComputations(x, r);
    Tuple rendered_color = Intersection::ShadeHit(w, comps);
    EXPECT_EQ(rendered_color, Tuple::color(0.38066, 0.47583, 0.2855, 1) );
}

TEST(WorldTestSuite, ShadeHitWith3Lights) {
    World w = World::DefaultWorld();
    w.lights.push_back(w.lights[0]);
    w.lights.push_back(w.lights[0]);
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = w.objects[0];
    Intersection x = Intersection(4, &s);
    Precompute comps = Intersection::PrepareComputations(x, r);
    Tuple rendered_color = Intersection::ShadeHit(w, comps);
    EXPECT_EQ(rendered_color, Tuple::color(0.38066, 0.47583, 0.2855, 1));
}

TEST(WorldTestSuite, ShadeHitIsGivenAnIntersectionInShadow) {
    World w;
    Light l1 = Light::PointLight(Tuple::point(0, 0, -10), Tuple::color(1, 1, 1, 1));
    w.lights.push_back(l1);
    Sphere s1;
    Sphere s2;
    s2.setTransform( Transformation::translation(0, 0, 10));
    w.objects.push_back(s1);
    w.objects.push_back(s2);

    Ray r = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    Intersection i = Intersection(4, &s2);
    Precompute comps = Intersection::PrepareComputations(i, r);
    Tuple rendered_color = Intersection::ShadeHit(w, comps);
    EXPECT_EQ( rendered_color, Tuple::color(0.1, 0.1, 0.1, 1) );
}

