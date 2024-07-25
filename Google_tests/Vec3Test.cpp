#include "gtest/gtest.h"
#include "Vec3.h"


class Vec3Fixture : public ::testing::Test {

protected:
    Vec3Fixture() : v1(nullptr), v2(nullptr) {} // Initialize pointers to nullptr

    // Member variables
    Vec3 *v1;
    Vec3 *v2;

    void SetUp() override {
        v1 = new Vec3(1, 2, 3);
        v2 = new Vec3(0, 0, 0);
    }

    void TearDown() override {
        delete v1;
        delete v2;
    }

};

TEST_F(Vec3Fixture, zeroVector){ // 1/1/1 -> 1/3/1

    v1->x = 0;
    v1->y = 0;
    v1->z = 0;

    EXPECT_EQ(v1->x, v2->x);
    EXPECT_EQ(v1->y, v2->y);
    EXPECT_EQ(v1->z, v2->z);

}

TEST_F(Vec3Fixture, OneTwoThreeVector){ // 3/1/100 -> 3/2/100

    v2->x = 1;
    v2->y = 2;
    v2->z = 3;

    EXPECT_EQ(v2->x, v1->x);
    EXPECT_EQ(v2->y, v1->y);
    EXPECT_EQ(v2->z, v1->z);
}