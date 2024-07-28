//
// Created by Craig Harris on 7/27/24.
//

#include "gtest/gtest.h"
#include "Tuple.h"
#include "Canvas.h"

TEST(CanvasTestSuite, CreateACanvasAllBlack) {
    Canvas c(10, 20);
    EXPECT_EQ(c.width, 10);
    EXPECT_EQ(c.height, 20);
    for (int h = 0; h < c.height; ++h){
        for (int w = 0; w < c.width; ++w) {
            EXPECT_EQ(c.pixels[h][w], Tuple::color(0, 0, 0, 1));
        }
    }
}

TEST(CanvasTestSuite, WriteToPixel) {
    Canvas c(10, 20);
    Tuple red = Tuple::color(1, 0, 0, 1);
    c.WritePixel(2, 3, red);
    for (int h = 0; h < c.height; ++h){
        for (int w = 0; w < c.width; ++w) {
            if (h == 3 && w == 2){
                EXPECT_EQ(c.pixels[h][w], Tuple::color(1, 0, 0, 1));
            }
            else
                EXPECT_EQ(c.pixels[h][w], Tuple::color(0, 0, 0, 1));
        }
    }
}

