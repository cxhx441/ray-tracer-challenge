//
// Created by Craig Harris on 7/29/24.
//

#include "gtest/gtest.h"
#include "patterns/StripedPattern.h"
#include "patterns/GradientPattern.h"
#include "patterns/CheckerPattern.h"
#include "patterns/RingPattern.h"
#include "patterns/TestPattern.h"
#include "shapes/Sphere.h"

class PatternFixture : public ::testing::Test {

protected:
    PatternFixture() : white(), black() {} // Initialize pointers to nullptr

    // Member variables
    Color white;
    Color black;

    void SetUp() override {
        white = Color::white();
        black = Color::black();
    }

    void TearDown() override {
//        delete white;
//        delete black;
    }
};

TEST_F(PatternFixture, CreateAStripePattern){
    StripedPattern pattern(white, black);
    EXPECT_EQ(pattern.color_a, white);
    EXPECT_EQ(pattern.color_b, black);
}

TEST_F(PatternFixture, StripePatternIsConstantInY){
    StripedPattern pattern(white, black);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 1, 0)), white);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 2, 0)), white);
}

TEST_F(PatternFixture, StripePatternIsConstantInZ){
    StripedPattern pattern(white, black);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 0, 1)), white);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 0, 2)), white);
}

TEST_F(PatternFixture, StripePatternAlternatesInX){
    StripedPattern pattern(white, black);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(0.9, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(1, 0, 0)), black);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(-0.1, 0, 0)), black);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(-1, 0, 0)), black);
    EXPECT_EQ(pattern.pattern_color_at(Tuple::point(-1.1, 0, 0)), white);
}

TEST_F(PatternFixture, StripesWithObjectTransformation){
    StripedPattern pattern(white, black);

    Sphere s;
    s.set_transform(Transformation::scaling(2));
    s.material.set_pattern(pattern);

    Tuple world_point(1.5, 0, 0, 1);

    EXPECT_EQ(s.pattern_at(world_point), white);
}

TEST_F(PatternFixture, StripesWithPatternTransformation){
    StripedPattern pattern(white, black);
    pattern.set_transform(Transformation::scaling(2));

    Sphere s;
    s.material.set_pattern(pattern);

    Tuple world_point(1.5, 0, 0, 1);

    EXPECT_EQ(s.pattern_at(world_point), white);
}

TEST_F(PatternFixture, StripesWithObjectAndPatternTransformation){
    StripedPattern pattern(white, black);
    pattern.set_transform(Transformation::scaling(2));

    Sphere s;
    s.set_transform(Transformation::scaling(2));
    s.material.set_pattern(pattern);

    Tuple world_point(1.5, 0, 0, 1);

    EXPECT_EQ(s.pattern_at(world_point), white);
}

TEST_F(PatternFixture, GradiatentPatternLinearlyInterpolatesBetweenColors){
    GradientPattern p(white, black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0.25, 0, 0)), Color(0.75, 0.75, 0.75, 1));
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0.5, 0, 0)), Color(0.5, 0.5, 0.5, 1));
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0.75, 0, 0)), Color(0.25, 0.25, 0.25, 1));
}

TEST_F(PatternFixture, RingShouldExtendInBothXAndZ){
    RingPattern p(white, black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(1, 0, 0)), black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 1)), black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0.708, 0, 0.708)), black);
}

TEST_F(PatternFixture, CheckersRepeatInX){
    CheckerPattern p(white, black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0.99, 0, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(1.01, 0, 0)), black);
}

TEST_F(PatternFixture, CheckersRepeatInY){
    CheckerPattern p(white, black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0.99, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 1.01, 0)), black);
}

TEST_F(PatternFixture, CheckersRepeatInZ){
    CheckerPattern p(white, black);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 0)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 0.99)), white);
    EXPECT_EQ(p.pattern_color_at(Tuple::point(0, 0, 1.01)), black);
}


TEST(TestPatternFixture, TestPatternDefaultTransform){
    TestPattern p;
    EXPECT_EQ(p.get_transform(), Matrix::identity(4));
}

TEST(TestPatternFixture, TestPatternCanTakeNewTransformation){
    TestPattern p;
    p.set_transform(Transformation::translation(1, 2, 3));
    EXPECT_EQ(p.get_transform(), Transformation::translation(1, 2, 3));
}

TEST(TestPatternFixture, TestPatternWIthAnObjectTranformation){
    Sphere s;
    s.set_transform(Transformation::scaling(2));
    TestPattern p;
    s.material.set_pattern(p);
    Color c = s.pattern_at(Tuple::point(2, 3, 4));
    EXPECT_EQ(c, Color(1, 1.5, 2, 1));
}

TEST(TestPatternFixture, TestPatternWithPatternTranformation){
    Sphere s;
    TestPattern p;
    p.set_transform(Transformation::scaling(2));
    s.material.set_pattern(p);
    Color c = s.pattern_at(Tuple::point(2, 3, 4));
    EXPECT_EQ(c, Color(1, 1.5, 2, 1));
}

TEST(TestPatternFixture, TestPatternWithBothObjectAndPatternTranformation){
    Sphere s;
    s.set_transform(Transformation::scaling(2));
    TestPattern p;
    p.set_transform(Transformation::translation(0.5, 1, 1.5));

    s.material.set_pattern(p);
    Color c = s.pattern_at(Tuple::point(2.5, 3, 3.5));
    EXPECT_EQ(c, Color(0.75, .5, .25, 1));
}

