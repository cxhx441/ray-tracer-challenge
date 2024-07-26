//
// Created by Craig Harris on 7/26/24.
//

#ifndef RAYTRACERCHAELLENGE_LINEARALGEBRA_H
#define RAYTRACERCHAELLENGE_LINEARALGEBRA_H

#include <stdexcept>

class Tuple {
public:
    float x, y, z;
    const float w;

    Tuple(float x, float y, float z, float w);

    static Tuple point(float x, float y, float z);
    static Tuple vector(float x, float y, float z);

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
    Tuple operator/(float scalar) const;


};

#endif //RAYTRACERCHAELLENGE_LINEARALGEBRA_H
