//
// Created by Craig Harris on 7/26/24.
//

#ifndef RAYTRACERCHAELLENGE_TUPLE_H
#define RAYTRACERCHAELLENGE_TUPLE_H

#include <stdexcept>

class Tuple {
public:
    float x, y, z, w;

    Tuple(float x, float y, float z, float w);

    static Tuple point(float x, float y, float z);
    static Tuple vector(float x, float y, float z);
    static Tuple color(float r, float g, float b, float a);
    float r() const;
    float g() const;
    float b() const;
    float a() const;
    void r(float r_val);
    void g(float g_val);
    void b(float b_val);
    void a(float a_val);

    static float magnitude(const Tuple &v);
    static Tuple normalize(const Tuple &v);
    static float dot(const Tuple& a, const Tuple& b);
    static Tuple cross(const Tuple& a, const Tuple& b);

    [[nodiscard]] bool isPoint() const;
    [[nodiscard]] bool isVector() const;

    bool operator==(const Tuple& other) const;
    bool operator!=(const Tuple& other) const;
    Tuple operator+(const Tuple& other) const;
    Tuple operator-(const Tuple& other) const;
    Tuple operator-() const;
    Tuple operator*(float scalar) const;
    Tuple operator*(const Tuple& other) const;
    Tuple operator/(float scalar) const;
    Tuple& operator+=(const Tuple& other);
    Tuple& operator-=(const Tuple& other);
    Tuple& operator*=(float scalar);
    Tuple& operator/=(float scalar);
    friend std::ostream& operator<<(std::ostream& os, const Tuple& t); // for printing

};

class Color : public Tuple {
public:
    Color();
    Color(float r, float g, float b, float a);
    float r();
    float g();
    float b();
    float a();
    void r(float r_val);
    void g(float g_val);
    void b(float b_val);
    void a(float a_val);
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
};


#endif //RAYTRACERCHAELLENGE_TUPLE_H
