//
// Created by Craig Harris on 7/26/24.
//
#include "LinearAlgebra.h"

Tuple4::Tuple4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
bool Tuple4::operator==(const Tuple4& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
}
bool Tuple4::operator!=(const Tuple4& other) const {
    return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
}
Tuple4 Tuple4::operator+(const Tuple4& other) const {
    if (w == 1 and other.w == 1) { throw std::invalid_argument("Cannot add two points"); }

    float _x = x + other.x;
    float _y = y + other.y;
    float _z = z + other.z;
    float _w = w + other.w;
    if (_w == 1.f){ return Point3 (_x, _y, _z); }
    else if (_w == 0.f){ return Vec3 ( _x, _y, _z); }
    else { throw std::invalid_argument("Resulting w not equal to 0 or 1"); }
}

Tuple4 Tuple4::operator-(const Tuple4& other) const {
    if (w == 0 and other.w == 1) { throw std::invalid_argument("Cannot subtract point from vector"); }

    float _x = x - other.x;
    float _y = y - other.y;
    float _z = z - other.z;
    float _w = w - other.w;
    if (_w == 1.f){ return Point3 (_x, _y, _z); }
    else if (_w == 0.f){ return Vec3 ( _x, _y, _z); }
    else { throw std::invalid_argument("Resulting w not equal to 0 or 1"); }
}
Tuple4 Tuple4::operator-() const { return { -x, -y, -z, w }; } //  SPECIFICALLY DEVIATING FROM BOOK BY NOT NEGATING W.

Point3::Point3() : Tuple4(0.f, 0.f, 0.f, 1.f) {}
Point3::Point3(float x, float y, float z) : Tuple4(x, y, z, 1.f) {}

Vec3::Vec3() : Tuple4(0.f, 0.f, 0.f, 0.f) {}
Vec3::Vec3(float x, float y, float z) : Tuple4(x, y, z, 0.f) {}
