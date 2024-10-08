//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "LightingModels.h"
#include "shapes/Sphere.h"
#include <cmath>

class LightingFixture : public ::testing::Test {

protected:
    LightingFixture() : m(nullptr), position(nullptr) {} // Initialize pointers to nullptr

    // Member variables
    Material *m;
    Tuple *position;
    Sphere s;

    void SetUp() override {
        m = new Material();
        position = new Tuple(); // point.
        position->w = 1; // point.
    }

    void TearDown() override {
        delete m;
        delete position;
    }
};

TEST_F(LightingFixture, LightingWithEyeBetweenLightAndSurface){
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color::white());
    bool in_shadow = false;
    Color result = LightingModels::phong_lighting(s.material, s, light, *position, eyev, normalv, in_shadow);
    EXPECT_EQ( result, Color(1.9, 1.9, 1.9, 1));
}

TEST_F(LightingFixture, LightingWithEyeBetweenLightAndSurface_EyeOffset45Deg){
    Tuple eyev = Tuple::vector(0, sqrt(2)/2, -sqrt(2)/2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color::white());
    bool in_shadow = false;
    Color result = LightingModels::phong_lighting(s.material, s, light, *position, eyev, normalv, in_shadow);
    EXPECT_EQ( result, Color(1.0, 1.0, 1.0, 1));
}

TEST_F(LightingFixture, LightingWithEyeOppositeSurface_LightOffset45Deg){
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 10, -10), Color::white());
    bool in_shadow = false;
    Color result = LightingModels::phong_lighting(s.material, s, light, *position, eyev, normalv, in_shadow);
    EXPECT_EQ( result, Color(0.7364, 0.7364, 0.7364, 1));
}

TEST_F(LightingFixture, LightingWithEyeInPathOfReflectionVector){
    Tuple eyev = Tuple::vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 10, -10), Color::white());
    bool in_shadow = false;
    Color result = LightingModels::phong_lighting(s.material, s, light, *position, eyev, normalv, in_shadow);
    EXPECT_EQ( result, Color(1.6364, 1.6364, 1.6364, 1) );
}

TEST_F(LightingFixture, LightingWithLightBehindSurface){
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, 10), Color::white());
    bool in_shadow = false;
    Color result = LightingModels::phong_lighting(s.material, s, light, *position, eyev, normalv, in_shadow);
    EXPECT_EQ( result, Color(0.1, 0.1, 0.1, 1) ); // just ambient since diff and spec go to 0. default material amb is 0.1
}

TEST_F(LightingFixture, LightingWithSurfaceInShadow){
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light(Tuple::point(0, 0, -10), Color::white());
    bool in_shadow = true;
    Color result = LightingModels::phong_lighting(s.material, s, light, *position, eyev, normalv, in_shadow);
    EXPECT_EQ( result, Color(0.1, 0.1, 0.1, 1));
}
