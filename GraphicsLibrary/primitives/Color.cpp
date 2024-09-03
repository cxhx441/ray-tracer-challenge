//
// Created by craig on 9/2/2024.
//

#include "Color.h"
#include <cmath>
#include <iostream>

Color::Color() : r(0), g(0), b(0), a(0) {}
Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}

Color Color::red()     { return {1.00, 0.00, 0.00}; }
Color Color::green()   { return {0.00, 1.00, 0.00}; }
Color Color::blue()    { return {0.00, 0.00, 1.00}; }
Color Color::yellow()  { return {1.00, 1.00, 0.00}; }
Color Color::magenta() { return {1.00, 0.00, 1.00}; }
Color Color::cyan()    { return {0.00, 1.00, 1.00}; }
Color Color::white()   { return {1.00, 1.00, 1.00}; }
Color Color::black()   { return {0.00, 0.00, 0.00}; }
Color Color::silver()  { return {0.75, 0.75, 0.75}; }
Color Color::gray()    { return {0.50, 0.50, 0.50}; }
Color Color::maroon()  { return {0.50, 0.00, 0.00}; };
Color Color::orange()  { return {1.00, 0.65, 0.00}; };
Color Color::navy()    { return {0.00, 0.00, 0.50}; };

bool Color::operator==(const Color& other) const {
    return (std::abs(r - other.r) < 10e-5) &&
           (std::abs(g - other.g) < 10e-5) &&
           (std::abs(b - other.b) < 10e-5) &&
           (std::abs(a - other.a) < 10e-5);
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

Color Color::operator+(const Color& other) const {
    return {
            r + other.r,
            g + other.g,
            b + other.b,
            a + other.a
    };
}

Color Color::operator-(const Color& other) const {
    return {
            r - other.r,
            g - other.g,
            b - other.b,
            a - other.a
    };
}


Color Color::operator-() const { return {-r, -g, -b, -a }; }

Color Color::operator*(const float scalar) const {
    return {
            r * scalar,
            g * scalar,
            b * scalar,
            a * scalar
    };
}

Color Color::operator*(const Color& other) const {
    return {
            r * other.r,
            g * other.g,
            b * other.b,
            a * other.a
    };
}

Color Color::operator/(const float scalar) const {
    return {
            r / scalar,
            g / scalar,
            b / scalar,
            a / scalar
    };
}

Color Color::operator/(const Color &other) const {
    return {
            r / other.r,
            g / other.g,
            b / other.b,
            a / other.a
    };
}

Color& Color::operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
}

Color& Color::operator-=(const Color& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    a -= other.a;
    return *this;
}

Color& Color::operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    a *= scalar;
    return *this;
}

Color& Color::operator/=(float scalar) {
    r /= scalar;
    g /= scalar;
    b /= scalar;
    a /= scalar;
    return *this;
}


// for printing
std::ostream& operator<<(std::ostream& os, const Color& t) {
    os << "(" << t.r << ", " << t.g << ", " << t.b << ", " << t.a << ")";
    return os;
}

