//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "Camera.h"
#include "Transformation.h"
#include "World.h"
#include "Canvas.h"
#include <cmath>

TEST(CameraTestSuite, ConstructingACamera){
    int h = 160;
    int v = 120;
    float field_of_view = M_PI/2.f;
    Camera c(h, v, field_of_view);
    EXPECT_EQ(h, c.hsize);
    EXPECT_EQ(v, c.vsize);
    EXPECT_FLOAT_EQ(field_of_view, c.fov);
    EXPECT_EQ(Matrix::identity(4), c.get_transform());
}

TEST(CameraTestSuite, PixelSizeForHorizontalCanvas){
    Camera c(200, 125, M_PI/2.f);
    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(CameraTestSuite, PixelSizeForVerticalCanvas){
    Camera c(125, 200, M_PI/2.f);
    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(CameraTestSuite, ConstructRayThroughCenterOfCanvas){
    Camera c(201, 101, M_PI/2.f);
    Ray r = Camera::ray_for_pixel(c, 100, 50);
    EXPECT_EQ(r.origin, Tuple::point(0, 0, 0));
    EXPECT_EQ(r.direction, Tuple::vector(0, 0, -1));
}

TEST(CameraTestSuite, ConstructRayThroughCornerOfCanvas){
    Camera c(201, 101, M_PI/2.f);
    Ray r = Camera::ray_for_pixel(c, 0, 0);
    EXPECT_EQ(r.origin, Tuple::point(0, 0, 0));
    EXPECT_EQ(r.direction, Tuple::vector(0.66519, 0.33259, -0.66851) );
}

TEST(CameraTestSuite, ConstructRayWhenCameraIsTransformed){
    Camera c(201, 101, M_PI/2.f);
    c.set_transform(Transformation::rotation_y(M_PI / 4.f) * Transformation::translation(0, -2, 5));
    Ray r = Camera::ray_for_pixel(c, 100, 50);
    EXPECT_EQ(r.origin, Tuple::point(0, 2, -5));
    EXPECT_EQ(r.direction, Tuple::vector(sqrtf(2)/2.f, 0, -sqrtf(2)/2.f));
}

TEST(CameraTestSuite, RenderingAWorldWithACamera){
    World w = World::DefaultWorld();
    Camera c(11, 11, M_PI/2.f);

    Tuple from = Tuple::point(0, 0, -5);
    Tuple to = Tuple::point(0, 0, 0);
    Tuple up = Tuple::vector(0, 1, 0);
    c.set_transform(Transformation::view_transform(from, to, up));

    Canvas image = Canvas::render(c, w);
    EXPECT_EQ(image.pixels[5][5], Tuple::color(0.38066, 0.47583, 0.2855, 1) );
}
