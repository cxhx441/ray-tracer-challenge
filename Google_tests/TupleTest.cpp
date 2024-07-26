
#include "gtest/gtest.h"
#include "Tuple.h"
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

TEST(TupleTestSuite, MagnitudeOfVec100) {
    Tuple v = Tuple::vector(1, 0, 0);
    EXPECT_EQ( Tuple::magnitude(v), 1);
}

TEST(TupleTestSuite, MagnitudeOfVec010) {
    Tuple v = Tuple::vector(0, 1, 0);
    EXPECT_EQ( Tuple::magnitude(v), 1);
}

TEST(TupleTestSuite, MagnitudeOfVec001) {
    Tuple v = Tuple::vector(0, 0, 1);
    EXPECT_EQ( Tuple::magnitude(v), 1);
}

TEST(TupleTestSuite, MagnitudeOfVec123) {
    Tuple v = Tuple::vector(1, 2, 3);
    EXPECT_FLOAT_EQ( Tuple::magnitude(v), std::sqrt(14));
}

TEST(TupleTestSuite, MagnitudeOfVecNeg123) {
    Tuple v = Tuple::vector(-1, -2, -3);
    EXPECT_FLOAT_EQ( Tuple::magnitude(v), std::sqrt(14));
}

TEST(TupleTestSuite, Normalize400) {
    Tuple v = Tuple::vector(4, 0, 0);
    EXPECT_EQ( Tuple::normalize(v), Tuple::vector(1, 0, 0));
}

TEST(TupleTestSuite, Normalize123) {
    Tuple v = Tuple::vector(1, 2, 3);
    Tuple n = Tuple::normalize(v);
    EXPECT_FLOAT_EQ(n.x, 1.f / std::sqrt(14));
    EXPECT_FLOAT_EQ(n.y, 2.f / std::sqrt(14));
    EXPECT_FLOAT_EQ(n.z, 3.f / std::sqrt(14));
}

TEST(TupleTestSuite, MagnitudeOfNormalizedVector) {
    Tuple v = Tuple::vector(1, 2, 3);
    Tuple n = Tuple::normalize(v);
    EXPECT_FLOAT_EQ(Tuple::magnitude(n), 1.f);
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



