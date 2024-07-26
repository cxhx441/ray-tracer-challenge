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

    Point3 p_default = Point3();
    EXPECT_EQ(p_default.x, 0.f);
    EXPECT_EQ(p_default.y, 0.f);
    EXPECT_EQ(p_default.z, 0.f);
    EXPECT_EQ(p_default.w, 1.f);
}

TEST(Point3TestSuite, EqualPoints){ // 12/2/2020 -> 737761
    Point3 p1 = Point3(4.3, -4.2, 3.1);
    Point3 p2 = Point3(4.3, -4.2, 3.1);
    EXPECT_EQ(p1, p2);
}

TEST(Point3TestSuite, NotEqualPoints){ // 12/2/2020 -> 737761
    Point3 p1 = Point3(4.3, -4.2, 3.1);
    Point3 p2 = Point3(4.31, -4.2, 3.1);
    EXPECT_NE(p1, p2);
}

TEST(Point3TestSuite, SettingPoints){ // 12/2/2020 -> 737761
    Point3 p = Point3();

    p.x = 4.3f;
    p.y = -4.2f;
    p.z = 3.1f;

    EXPECT_EQ(p.x, 4.3f);
    EXPECT_EQ(p.y, -4.2f);
    EXPECT_EQ(p.z, 3.1f);
    EXPECT_EQ(p.w, 1.f);
}
TEST(Point3TestSuite, PointAddition){ // 12/2/2020 -> 737761
    Point3 p1 = Point3();
    Point3 p2 = Point3();

    EXPECT_THROW(p1 + p2, std::invalid_argument);
}