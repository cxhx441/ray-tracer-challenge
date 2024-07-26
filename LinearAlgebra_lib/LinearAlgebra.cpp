//
// Created by Craig Harris on 7/26/24.
//
#include "LinearAlgebra.h"
#include <cmath>

Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Tuple Tuple::point(float x, float y, float z) {
    return {x, y, z, 1.0f};
}

Tuple Tuple::vector(float x, float y, float z) {
    return {x, y, z, 0.0f};
}

[[nodiscard]] bool Tuple::isPoint() const { return w == 1.0f; }
[[nodiscard]] bool Tuple::isVector() const { return w == 0.0f; }

float Tuple::magnitude(const Tuple& v) {
    return std:: sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Tuple Tuple::normalize(const Tuple& v) {
    return vector(v.x, v.y, v.z) / magnitude(v);
}

float Tuple::dot(const Tuple& a, const Tuple& b){
    return a.x * b.x +
            a.y * b.y +
            a.z * b.z +
            a.w * b.w;
}

Tuple Tuple::cross(const Tuple& a, const Tuple& b){
    return vector(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
    );
}

bool Tuple::operator==(const Tuple& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
}

bool Tuple::operator!=(const Tuple& other) const {
    return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
}

Tuple Tuple::operator+(const Tuple& other) const {
    return {
        x + other.x,
        y + other.y,
        z + other.z,
        w + other.w
    };
}

Tuple Tuple::operator-(const Tuple& other) const {
    return {
        x - other.x,
        y - other.y,
        z - other.z,
        w - other.w
    };
}

Tuple Tuple::operator-() const { return {-x, -y, -z, -w }; }

Tuple Tuple::operator*(const float scalar) const {
    return {
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
    };
}

Tuple Tuple::operator/(const float scalar) const {
    return {
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar
    };
}
