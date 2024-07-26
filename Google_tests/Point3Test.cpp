#include "gtest/gtest.h"
#include "LinearAlgebra.h"


TEST(Point3TestSuite, ExamplePoint){ // 12/2/2020 -> 737761
    Point3 p = Point3(4.3, -4.2, 3.1);
    EXPECT_EQ(p.x, 4.3f);
    EXPECT_EQ(p.y, -4.2f);
    EXPECT_EQ(p.z, 3.1f);
    EXPECT_EQ(p.w, 1.f);
}


TEST(Point3TestSuite, ZeroPoint){ // 12/0/2020 -> 0
    Point3 p = Point3(0, 0, 0);
    EXPECT_EQ(p.x, 0.f);
    EXPECT_EQ(p.y, 0.f);
    EXPECT_EQ(p.z, 0.f);
    EXPECT_EQ(p.w, 1.f);

    Point3 p2 = Point3();
    EXPECT_EQ(p2.x, 0.f);
    EXPECT_EQ(p2.y, 0.f);
    EXPECT_EQ(p2.z, 0.f);
    EXPECT_EQ(p2.w, 1.f);
}

TEST(Point3TestSuite, EqualPoints){ // 12/2/2020 -> 737761
    Point3 p1 = Point3(4.3, -4.2, 3.1);
    Point3 p2 = Point3(4.3, -4.2, 3.1);
    Vec3 v2 = Vec3(4.3, -4.2, 3.1);
    EXPECT_EQ(p1, p2);
}

TEST(Point3TestSuite, UnequalPoints){ // 12/2/2020 -> 737761
    Point3 p1 = Point3(4.3, -4.2, 3.1);
    Point3 p2 = Point3(4.31, -4.2, 3.1);
    EXPECT_NE(p1, p2);
}
