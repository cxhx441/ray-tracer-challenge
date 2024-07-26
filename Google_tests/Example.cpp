#include "gtest/gtest.h"
#include "LinearAlgebra.h"

// EXAMPLE
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
