
#include "gtest/gtest.h"
#include "primitives/Color.h"
#include <cmath>

TEST(TupleTestSuite, ColorsAreRGB) {
    Color c(-0.5, 0.4, 1.7, 1);
    EXPECT_FLOAT_EQ(c.r, -0.5);
    EXPECT_FLOAT_EQ(c.g, 0.4);
    EXPECT_FLOAT_EQ(c.b, 1.7);
    EXPECT_FLOAT_EQ(c.a, 1);
}

TEST(TupleTestSuite, ColorEqualityAfterAddition) {
    Color c1(0.9, 0.6, 0.75, 1);
    Color c2(0.7, 0.1, 0.25, 1);
    EXPECT_EQ(c1 + c2, Color(1.6, 0.7, 1, 2));
}

TEST(TupleTestSuite, ColorEqualityAfterSubtraction) {
    Color c1(0.9, 0.6, 0.75, 1);
    Color c2(0.7, 0.1, 0.25, 1);
    EXPECT_EQ(c1 - c2, Color(0.2, 0.5, 0.5, 0));
}

TEST(TupleTestSuite, ColorEqualityAfterScalarMultiplication) {
    Color c1(0.2, 0.3, 0.4, 1);
    EXPECT_EQ(c1 * 2, Color(0.4, 0.6, 0.8, 2));
}

TEST(TupleTestSuite, ColorEqualityAfterMultiplication) {
    Color c1(1, 0.2, 0.4, 1);
    Color c2(0.9, 1, 0.1, 1);
    EXPECT_EQ(c1 * c2, Color(0.9, 0.2, 0.04, 1));
}
