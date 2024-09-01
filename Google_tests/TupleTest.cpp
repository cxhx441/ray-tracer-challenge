
#include "gtest/gtest.h"
#include "primitives/Tuple.h"
#include <cmath>

TEST(TupleTestSuite, TupleWithW1IsPoint) {
    Tuple a(4.3, -4.2, 3.1, 1.0);
    EXPECT_EQ(a.x, 4.3f);
    EXPECT_EQ(a.y, -4.2f);
    EXPECT_EQ(a.z, 3.1f);
    EXPECT_EQ(a.w, 1.f);
    EXPECT_TRUE(a.isPoint());
    EXPECT_FALSE(a.isVector());
}

TEST(TupleTestSuite, TupleWithW0IsVector) {
    Tuple a(4.3, -4.2, 3.1, 0.0);
    EXPECT_EQ(a.x, 4.3f);
    EXPECT_EQ(a.y, -4.2f);
    EXPECT_EQ(a.z, 3.1f);
    EXPECT_EQ(a.w, 0.f);
    EXPECT_FALSE(a.isPoint());
    EXPECT_TRUE(a.isVector());
}

TEST(TupleTestSuite, pointCreatesTupleWithW1) {
    Tuple p = Tuple::point(4, -4, 3);
    EXPECT_EQ(p, Tuple(4, -4, 3, 1));
}

TEST(TupleTestSuite, vectorCreatesTupleWithW0) {
    Tuple v = Tuple::vector(4, -4, 3);
    EXPECT_EQ(v, Tuple(4, -4, 3, 0));
}

TEST(TupleTestSuite, AddingTwoTuples) {
    Tuple a1(3, -2, 5, 1);
    Tuple a2(-2, 3, 1, 0);
    EXPECT_EQ( a1 + a2, Tuple(1, 1, 6, 1) );
}


TEST(TupleTestSuite, SubtractTwoPoints) {
    Tuple p1 = Tuple::point(3, 2, 1);
    Tuple p2 = Tuple::point(5, 6, 7);
    EXPECT_EQ( p1 - p2, Tuple::vector(-2, -4, -6) );
}

TEST(TupleTestSuite, SubtractVectorFromPoint) {
    Tuple p = Tuple::point(3, 2, 1);
    Tuple v = Tuple::vector(5, 6, 7);
    EXPECT_EQ( p - v, Tuple::point(-2, -4, -6) );
}

TEST(TupleTestSuite, SubtractTwoVectors) {
    Tuple v1 = Tuple::vector(3, 2, 1);
    Tuple v2 = Tuple::vector(5, 6, 7);
    EXPECT_EQ( v1 - v2, Tuple::vector(-2, -4, -6) );
}

TEST(TupleTestSuite, SubtractVectorFromZeroVector) {
    Tuple zero = Tuple::vector(0, 0, 0);
    Tuple v = Tuple::vector(1, -2, 3);
    EXPECT_EQ( zero - v, Tuple::vector(-1, 2, -3) );
}

TEST(TupleTestSuite, NegatingATuple) {
    Tuple a(1, -2, 3, -4);
    EXPECT_EQ( -a, Tuple(-1, 2, -3, 4) );
}

TEST(TupleTestSuite, MultiplyingTupleByScalar) {
    Tuple a(1, -2, 3, -4);
    EXPECT_EQ( a * 3.5, Tuple(3.5, -7, 10.5, -14) );
}

TEST(TupleTestSuite, MultiplyingTupleByFraction) {
    Tuple a(1, -2, 3, -4);
    EXPECT_EQ( a * 0.5, Tuple(0.5, -1, 1.5, -2) );
}

TEST(TupleTestSuite, DivideTupleByScalar) {
    Tuple a(1, -2, 3, -4);
    EXPECT_EQ( a / 2, Tuple(0.5, -1, 1.5, -2) );
}

TEST(TupleTestSuite, AddingTupleToExisting) {
    Tuple a1(3, -2, 5, 1);
    Tuple a2(-2, 3, 1, 0);
    a1 += a2;
    EXPECT_EQ( a1, Tuple(1, 1, 6, 1) );
}

TEST(TupleTestSuite, SubtractTupleFromExisting) {
    Tuple v1 = Tuple::vector(3, 2, 1);
    Tuple v2 = Tuple::vector(5, 6, 7);
    v1 -= v2;
    EXPECT_EQ(v1, Tuple::vector(-2, -4, -6) );
}

TEST(TupleTestSuite, MultiplyingExisting) {
    Tuple a(1, -2, 3, -4);
    a *= 3.5;
    EXPECT_EQ( a, Tuple(3.5, -7, 10.5, -14) );
}

TEST(TupleTestSuite, DivideExisting) {
    Tuple a(1, -2, 3, -4);
    a /= 2;
    EXPECT_EQ( a, Tuple(0.5, -1, 1.5, -2) );
}

TEST(TupleTestSuite, MagnitudeOfVec100) {
    Tuple v = Tuple::vector(1, 0, 0);
    EXPECT_EQ( v.magnitude(), 1);
}

TEST(TupleTestSuite, MagnitudeOfVec010) {
    Tuple v = Tuple::vector(0, 1, 0);
    EXPECT_EQ( v.magnitude(), 1);
}

TEST(TupleTestSuite, MagnitudeOfVec001) {
    Tuple v = Tuple::vector(0, 0, 1);
    EXPECT_EQ( v.magnitude(), 1);
}

TEST(TupleTestSuite, MagnitudeOfVec123) {
    Tuple v = Tuple::vector(1, 2, 3);
    EXPECT_FLOAT_EQ( v.magnitude(), std::sqrt(14));
}

TEST(TupleTestSuite, MagnitudeOfVecNeg123) {
    Tuple v = Tuple::vector(-1, -2, -3);
    EXPECT_FLOAT_EQ( v.magnitude(), std::sqrt(14));
}

TEST(TupleTestSuite, Normalize400) {
    Tuple v = Tuple::vector(4, 0, 0);
    EXPECT_EQ(Tuple::normalized(v), Tuple::vector(1, 0, 0));
}

TEST(TupleTestSuite, Normalize123) {
    Tuple v = Tuple::vector(1, 2, 3);
    Tuple n = Tuple::normalized(v);
    EXPECT_FLOAT_EQ(n.x, 1.f / std::sqrt(14));
    EXPECT_FLOAT_EQ(n.y, 2.f / std::sqrt(14));
    EXPECT_FLOAT_EQ(n.z, 3.f / std::sqrt(14));
}

TEST(TupleTestSuite, MagnitudeOfNormalizedVector) {
    Tuple v = Tuple::vector(1, 2, 3);
    Tuple n = Tuple::normalized(v);
    EXPECT_FLOAT_EQ(n.magnitude(), 1.f);
}

TEST(TupleTestSuite, DotProductOfTwoTuples) {
    Tuple a = Tuple::vector(1, 2, 3);
    Tuple b = Tuple::vector(2, 3, 4);
    EXPECT_EQ(Tuple::dot(a, b), 20.f);
}

TEST(TupleTestSuite, CrossProductOfTwoTuples) {
    Tuple v1 = Tuple::vector(1, 2, 3);
    Tuple v2 = Tuple::vector(2, 3, 4);
    EXPECT_EQ(Tuple::cross(v1, v2), Tuple::vector(-1, 2, -1) );
    EXPECT_EQ(Tuple::cross(v2, v1), Tuple::vector(1, -2, 1) );
}

TEST(TupleTestSuite, ColorsAreRGB) {
    Tuple c = Tuple::color(-0.5, 0.4, 1.7, 1);
    EXPECT_FLOAT_EQ(c.r(), -0.5);
    EXPECT_FLOAT_EQ(c.g(), 0.4);
    EXPECT_FLOAT_EQ(c.b(), 1.7);
    EXPECT_FLOAT_EQ(c.a(), 1);
}

TEST(TupleTestSuite, ColorEqualityAfterAddition) {
    Tuple c1 = Tuple::color(0.9, 0.6, 0.75, 1);
    Tuple c2 = Tuple::color(0.7, 0.1, 0.25, 1);
    EXPECT_EQ(c1 + c2, Tuple::color(1.6, 0.7, 1, 2));
}

TEST(TupleTestSuite, ColorEqualityAfterSubtraction) {
    Tuple c1 = Tuple::color(0.9, 0.6, 0.75, 1);
    Tuple c2 = Tuple::color(0.7, 0.1, 0.25, 1);
    EXPECT_EQ(c1 - c2, Tuple::color(0.2, 0.5, 0.5, 0));
}

TEST(TupleTestSuite, ColorEqualityAfterScalarMultiplication) {
    Tuple c1 = Tuple::color(0.2, 0.3, 0.4, 1);
    EXPECT_EQ(c1 * 2, Tuple::color(0.4, 0.6, 0.8, 2));
}

TEST(TupleTestSuite, ColorEqualityAfterMultiplication) {
    Tuple c1 = Tuple::color(1, 0.2, 0.4, 1);
    Tuple c2 = Tuple::color(0.9, 1, 0.1, 1);
    EXPECT_EQ(c1 * c2, Tuple::color(0.9, 0.2, 0.04, 1));
}

TEST(TupleTestSuite, ReflectVectorApproachingAt45Deg) {
    Tuple inV = Tuple::vector(1, -1, 0);
    Tuple n = Tuple::vector(0, 1, 0);
    Tuple outV = Tuple::reflected(inV, n);
    EXPECT_EQ(outV, Tuple::vector(1, 1, 0));
}

TEST(TupleTestSuite, ReflectVectorOffSlantedSurface) {
    Tuple inV = Tuple::vector(0, -1, 0);
    Tuple n = Tuple::vector(sqrt(2)/2.f, sqrt(2)/2.f, 0);
    Tuple outV = Tuple::reflected(inV, n);
    EXPECT_EQ(outV, Tuple::vector(1, 0, 0));
}
