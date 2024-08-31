//
// Created by Craig Harris on 7/27/24.
//

#include "gtest/gtest.h"
#include "primitives/Tuple.h"
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
    c.write_pixel(2, 3, red);
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

TEST(CanvasTestSUite, ConstructPPMHeader){
    Canvas c(5, 3);
    std::string ppm = c.to_ppm_str();
    std::istringstream stream(ppm);
    std::string line;
    std::string header;
    int i = 0;
    while (i < 3 && std::getline(stream, line)){
        header.append(line + "\n");
        i += 1;
    }
    std::string trueHeader("P3\n5 3\n255\n");
    EXPECT_EQ(header, trueHeader);
}

TEST(CanvasTestSUite, ConstructPPMPixelData){
    Canvas c(5, 3);

    Tuple c1 = Tuple::color(1.5, 0.0, 0.0, 1.0);
    Tuple c2 = Tuple::color(0.0, 0.5, 0.0, 1.0);
    Tuple c3 = Tuple::color(-0.5, 0.0, 1.0, 1.0);

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);

    std::string ppm = c.to_ppm_str();
    std::istringstream stream(ppm);
    std::string line;
    std::string header;
    int i = 0;
    while (std::getline(stream, line)){
        if (i >= 3)
            header.append(line + "\n");
        i += 1;
    }
    std::string trueHeader;
    trueHeader.append("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n");
    trueHeader.append("0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 \n");
    trueHeader.append("0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n");
    EXPECT_EQ(header, trueHeader);
}

TEST(CanvasTestSUite, PPMSplitLongLines){
    Canvas c(10, 2);

    Tuple c1 = Tuple::color(1, 0.8, 0.6, 1);
    c.fill_pixels(c1);

    std::string ppm = c.to_ppm_str();
    std::istringstream stream(ppm);
    std::string line;
    std::string header;
    int i = 0;
    while (std::getline(stream, line)){
        if (i >= 3)
            header.append(line + "\n");
        i += 1;
    }
    std::string trueHeader;
    trueHeader.append("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 \n");
    trueHeader.append("153 255 204 153 255 204 153 255 204 153 255 204 153 \n");
    trueHeader.append("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 \n");
    trueHeader.append("153 255 204 153 255 204 153 255 204 153 255 204 153 \n");
    EXPECT_EQ(header, trueHeader);
}
