//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Material.h"

TEST(MaterialTestSuite, DefaultMaterial){
    Material m = Material();
    EXPECT_EQ(m.color, Tuple::color(1, 1, 1, 1));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
}

