//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Material.h"
#include "patterns/StripedPattern.h"
#include "lights/PointLight.h"
#include "LightingModels.h"
#include "shapes/Sphere.h"

TEST(MaterialTestSuite, DefaultMaterial){
    Material m = Material();
    EXPECT_EQ(m.color, Color::white());
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
    EXPECT_FLOAT_EQ(m.reflective, 0);
    EXPECT_FALSE(m.has_pattern());
}

TEST(MaterialTestSuite, LightingWithPatternApplied){
    Sphere s;
    StripedPattern p = StripedPattern(Color::white(), Color::black());
    s.material.set_pattern(p);
    s.material.ambient = 1;
    s.material.diffuse = 0;
    s.material.specular = 0;
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color::white());
    Color c1 = LightingModels::phong_lighting(s.material, s, light, Tuple::point(0.9, 0, 0), eyev, normalv, false);
    Color c2 = LightingModels::phong_lighting(s.material, s, light, Tuple::point(1.1, 0, 0), eyev, normalv, false);
    EXPECT_EQ(c1, Color::white());
    EXPECT_EQ(c2, Color::black());
}

TEST(MaterialTestSuite, TransparencyAndRefractiveIndexForDefaultMaterial){
    Material m;
    EXPECT_EQ(m.transparency, 0.0);
    EXPECT_EQ(m.refractive_index, 1.0);
}

