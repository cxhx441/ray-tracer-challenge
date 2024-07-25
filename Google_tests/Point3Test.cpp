#include "gtest/gtest.h"
#include "Point3.h"


TEST(Point3TestSuite, ExamplePoint){ // 12/2/2020 -> 737761
    Point3 p = Point3(1, 2, 3);
    EXPECT_EQ(p.x, 1);
//    EXPECT_EQ(p.y, 2);
//    EXPECT_EQ(p.z, 3);
//    EXPECT_EQ(p.w, 1);
}


TEST(Point3TestSuite, IncorrectPoint){ // 12/0/2020 -> 0
    Point3 p = Point3(1, 2, 3);
    ASSERT_EQ(p.x, 1);
}