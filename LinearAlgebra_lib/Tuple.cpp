//
// Created by Craig Harris on 7/26/24.
//
#include "Tuple.h"
#include <cmath>
#include <iostream>

Tuple::Tuple() : x(0), y(0), z(0), w(0) {}
Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Tuple Tuple::point(float x, float y, float z) {
    return {x, y, z, 1.0f};
}

Tuple Tuple::vector(float x, float y, float z) {
    return {x, y, z, 0.0f};
}

Tuple Tuple::color(float r, float g, float b, float a) {
    return {r, g, b, a};
}
float Tuple::r() const { return x; }
float Tuple::g() const { return y; }
float Tuple::b() const { return z; }
float Tuple::a() const { return w; }
void Tuple::r(float r) { x = r; }
void Tuple::g(float g) { y = g; }
void Tuple::b(float b) { z = b; }
void Tuple::a(float a) { w = a; }

bool Tuple::isPoint() const { return w != 0.0f; }
bool Tuple::isVector() const { return w == 0.0f; }

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

Tuple Tuple::reflect(const Tuple &v, const Tuple &n) {
    return v - ( n * 2 * dot(v, n) );
}


bool Tuple::operator==(const Tuple& other) const {
    return (std::abs(x - other.x) < 10e-5) &&
         (std::abs(y - other.y) < 10e-5) &&
         (std::abs(z - other.z) < 10e-5) &&
         (std::abs(w - other.w) < 10e-5);
}

bool Tuple::operator!=(const Tuple& other) const {
    return !(*this == other);
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

Tuple Tuple::operator*(const Tuple& other) const {
    return {
            x * other.x,
            y * other.y,
            z * other.z,
            w * other.w
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

Tuple& Tuple::operator+=(const Tuple& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Tuple& Tuple::operator-=(const Tuple& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Tuple& Tuple::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Tuple& Tuple::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}


// for printing
std::ostream& operator<<(std::ostream& os, const Tuple& t) {
    os << "(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
    return os;
}

