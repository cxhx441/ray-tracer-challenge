#include "gtest/gtest.h"
#include "LinearAlgebra.h"


class Vec3Fixture : public ::testing::Test {

protected:
    Vec3Fixture() : v1(nullptr), vZero(nullptr) {} // Initialize pointers to nullptr

    // Member variables
    Vec3 *v1;
    Vec3 *vZero;

    void SetUp() override {
        v1 = new Vec3(1, 2, 3);
        vZero = new Vec3();
    }

    void TearDown() override {
        delete v1;
        delete vZero;
    }

};
TEST(Vec3TestSuite, ExampleVector){ // 12/2/2020 -> 737761
    Vec3 v = Vec3(4.3, -4.2, 3.1);
    EXPECT_EQ(v.x, 4.3f);
    EXPECT_EQ(v.y, -4.2f);
    EXPECT_EQ(v.z, 3.1f);
    EXPECT_EQ(v.w, 0.f);
}


TEST(Vec3TestSuite, ZeroVector){ // 12/0/2020 -> 0
    Vec3 v = Vec3(0, 0, 0);
    EXPECT_EQ(v.x, 0.f);
    EXPECT_EQ(v.y, 0.f);
    EXPECT_EQ(v.z, 0.f);
    EXPECT_EQ(v.w, 0.f);

    Vec3 v_default = Vec3();
    EXPECT_EQ(v_default.x, 0.f);
    EXPECT_EQ(v_default.y, 0.f);
    EXPECT_EQ(v_default.z, 0.f);
    EXPECT_EQ(v_default.w, 0.f);
}

TEST(Vec3TestSuite, EqualVector){ // 12/2/2020 -> 737761
    Vec3 v1 = Vec3(4.3, -4.2, 3.1);
    Vec3 v2 = Vec3(4.3, -4.2, 3.1);
    EXPECT_EQ(v1, v2);
}

TEST(Vec3TestSuite, NotEqualVector){ // 12/2/2020 -> 737761
    Vec3 v1 = Vec3(4.3, -4.2, 3.1);
    Vec3 v2 = Vec3(4.31, -4.2, 3.1);
    EXPECT_NE(v1, v2);
}

TEST(Vec3TestSuite, SettingVector){ // 12/2/2020 -> 737761
    Vec3 v = Vec3();

    v.x = 4.3f;
    v.y = -4.2f;
    v.z = 3.1f;

    EXPECT_EQ(v.x, 4.3f);
    EXPECT_EQ(v.y, -4.2f);
    EXPECT_EQ(v.z, 3.1f);
    EXPECT_EQ(v.w, 0.f);
}

TEST(Vec3TestSuite, VectorNotEqualPoint){ // 12/2/2020 -> 737761
    Point3 p = Point3();
    Vec3 v = Vec3();
    EXPECT_NE(p, v);
}
TEST(Vec3TestSuite, VectorAddition){ // 12/2/2020 -> 737761
    Vec3 v1 = Vec3();
    Vec3 v2 = Vec3(1, 2, 3);

    EXPECT_EQ(Vec3(1, 2, 3), v1 + v2);
}
TEST(Vec3TestSuite, VectorPointAddition){ // 12/2/2020 -> 737761
    Point3 p = Point3(-1, -2, -3);
    Vec3 v = Vec3(1, 2, 3);

    EXPECT_EQ(Point3(0, 0, 0), p + v);
}

TEST(Tuple4TestSuite, SubtractTwoPoints) { // 12/2/2020 -> 737761
    Point3 p1 = Point3(3, 2, 1);
    Point3 p2 = Point3(5, 6, 7);
    EXPECT_EQ(Vec3(-2, -4, -6), p1 - p2);
}

TEST(Tuple4TestSuite, SubtractVectorFromPoint) { // 12/2/2020 -> 737761
    Point3 p = Point3(3, 2, 1);
    Vec3 v = Vec3(5, 6, 7);
    EXPECT_EQ(Point3(-2, -4, -6), p - v);
}

TEST(Tuple4TestSuite, SubtractTwoVectors) { // 12/2/2020 -> 737761
    Vec3 v1 = Vec3(3, 2, 1);
    Vec3 v2 = Vec3(5, 6, 7);
    EXPECT_EQ(Vec3(-2, -4, -6), v1 - v2);
}

TEST(Tuple4TestSuite, SubtractPointFromVector) { // 12/2/2020 -> 737761
    Point3 p = Point3(3, 2, 1);
    Vec3 v = Vec3(5, 6, 7);
    EXPECT_THROW(v - p, std::invalid_argument);
}

TEST(Tuple4TestSuite, TupleNegation){ // 12/2/2020 -> 737761
    Vec3 v = Vec3(1, 2, 3);
    Point3 p = Point3(1, 2, 3);
    Tuple4 t = Tuple4(1, 2, 3, 4);

    EXPECT_EQ(Tuple4(-1, -2, -3, 0), -v);
    EXPECT_EQ(Tuple4(-1, -2, -3, -1), -p);
    EXPECT_EQ(Tuple4(-1, -2, -3, -4), -t);
}
