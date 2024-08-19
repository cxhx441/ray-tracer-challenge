//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "World.h"
#include "Ray.h"
#include "Intersection.h"

TEST(WorldTestSuite, CreateDefaultWorld){
    World w = World::DefaultWorld();

    EXPECT_EQ(w.light.position, Tuple::point(-10, 10, -10) );
    EXPECT_EQ(w.light.intensity, Tuple::color(1, 1, 1, 1) );

    ASSERT_EQ(w.objects.size(), 2);

    EXPECT_EQ(w.objects[0].material.color, Tuple::color(0.8, 1.0, 0.6, 1) );
    EXPECT_FLOAT_EQ(w.objects[0].material.diffuse, 0.7);
    EXPECT_FLOAT_EQ(w.objects[0].material.specular, 0.2);

    EXPECT_EQ(w.objects[1].transformation, Transformation::scaling(0.5) );
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

