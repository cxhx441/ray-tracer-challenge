//
// Created by Craig Harris on 7/26/24.
//
#include "LinearAlgebra.h"

Tuple3::Tuple3() : x(0), y(0), z(0) {}
Tuple3::Tuple3(float x, float y, float z) : x(x), y(y), z(z) {}
bool Tuple3::operator==(const Tuple3& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
}
bool Tuple3::operator!=(const Tuple3& other) const {
    return (x != other.x) || (y != other.y) || (z == other.z);
}

Point3::Point3() : Tuple3(), w(1.0f) {}
Point3::Point3(float x, float y, float z) : Tuple3(x, y, z), w(1.0f) {}
bool Point3::operator==(const Point3& other) const {
    return Tuple3::operator==(other) && w == other.w;
}
bool Point3::operator!=(const Point3& other) const {
    return Tuple3::operator!=(other) || w != other.w;
}

Vec3::Vec3() : Tuple3(), w(0.0f) {}
Vec3::Vec3(float x, float y, float z) : Tuple3(x, y, z), w(0.0f) {}
bool Vec3::operator==(const Vec3& other) const {
    return Tuple3::operator==(other) && w == other.w;
}
bool Vec3::operator!=(const Vec3& other) const {
    return Tuple3::operator!=(other) || w != other.w;
}
