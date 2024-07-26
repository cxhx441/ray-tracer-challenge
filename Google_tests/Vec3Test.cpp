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

TEST_F(Vec3Fixture, zeroVector){ // 1/1/1 -> 1/3/1

    v1->x = 0;
    v1->y = 0;
    v1->z = 0;

    EXPECT_EQ(v1->x, vZero->x);
    EXPECT_EQ(v1->y, vZero->y);
    EXPECT_EQ(v1->z, vZero->z);

}

TEST_F(Vec3Fixture, OneTwoThreeVector){ // 3/1/100 -> 3/2/100

    vZero->x = 1;
    vZero->y = 2;
    vZero->z = 3;

    EXPECT_EQ(vZero->x, v1->x);
    EXPECT_EQ(vZero->y, v1->y);
    EXPECT_EQ(vZero->z, v1->z);
}