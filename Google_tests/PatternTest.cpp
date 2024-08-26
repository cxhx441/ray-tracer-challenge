//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "StripedPattern.h"

class PatternFixture : public ::testing::Test {

protected:
    PatternFixture() : white(), black() {} // Initialize pointers to nullptr

    // Member variables
    Tuple white;
    Tuple black;

    void SetUp() override {
        white = Tuple::color(1, 1, 1, 1);
        black = Tuple::color(0, 0, 0, 1);
    }

    void TearDown() override {
//        delete white;
//        delete black;
    }
};

TEST_F(PatternFixture, CreateAStripePattern){
    StripedPattern p = StripedPattern(white, black);
    EXPECT_EQ(p.color_a, white);
    EXPECT_EQ(p.color_b, black);
}

TEST_F(PatternFixture, StripePatternIsConstantInY){
    StripedPattern p = StripedPattern(white, black);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 1, 0)), white);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 2, 0)), white);
}

TEST_F(PatternFixture, StripePatternIsConstantInZ){
    StripedPattern p = StripedPattern(white, black);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 0, 1)), white);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 0, 2)), white);
}

TEST_F(PatternFixture, StripePatternAlternatesInX){
    StripedPattern p = StripedPattern(white, black);
    EXPECT_EQ(p.stripe_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(Tuple::point(0.9, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(Tuple::point(1, 0, 0)), black);
    EXPECT_EQ(p.stripe_at(Tuple::point(-0.1, 0, 0)), black);
    EXPECT_EQ(p.stripe_at(Tuple::point(-1, 0, 0)), black);
    EXPECT_EQ(p.stripe_at(Tuple::point(-1.1, 0, 0)), white);
}
