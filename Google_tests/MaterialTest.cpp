//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Material.h"
#include "StripedPattern.h"
#include "PointLight.h"
#include "Lighting.h"
#include "Sphere.h"

TEST(MaterialTestSuite, DefaultMaterial){
    Material m = Material();
    EXPECT_EQ(m.color, Tuple::color(1, 1, 1, 1));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
    EXPECT_EQ(m.pattern, nullptr);
}

TEST(MaterialTestSuite, LightingWithPatternApplied){
    Sphere s;
    Pattern *p = new StripedPattern(Tuple::color(1, 1, 1, 1), Tuple::color(0, 0, 0, 1));
    s.material.set_pattern(p);
    s.material.ambient = 1;
    s.material.diffuse = 0;
    s.material.specular = 0;
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Tuple::color(1, 1, 1, 1));
    Tuple c1 = Lighting::phong_lighting(s.material, s, light, Tuple::point(0.9, 0, 0), eyev, normalv, false);
    Tuple c2 = Lighting::phong_lighting(s.material, s, light, Tuple::point(1.1, 0, 0), eyev, normalv, false);
    EXPECT_EQ(c1, Tuple::color(1, 1, 1, 1));
    EXPECT_EQ(c2, Tuple::color(0, 0, 0, 1));
}
