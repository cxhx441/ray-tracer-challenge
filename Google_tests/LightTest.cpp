//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "lights/PointLight.h"

TEST(LightTestSuite, PointLightHasPositionAndIntensity){
    Color intensity = Color::white();
    Tuple pos = Tuple::point(0, 0, 0);
    PointLight light(pos, intensity);
    EXPECT_EQ(light.point, pos);
    EXPECT_EQ(light.color, intensity);
}

