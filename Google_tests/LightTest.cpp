//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Light.h"

TEST(LightTestSuite, PointLightHasPositionAndIntensity){
    Tuple inten = Tuple::color(1, 1, 1, 1);
    Tuple pos = Tuple::point(0, 0, 0);
    Light light = Light::PointLight(pos, inten);
    EXPECT_EQ( light.position, pos);
    EXPECT_EQ(light.intensity, inten);
}

