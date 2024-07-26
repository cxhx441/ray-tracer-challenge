//
// Created by Craig Harris on 7/26/24.
//

#ifndef RAYTRACERCHAELLENGE_LINEARALGEBRA_H
#define RAYTRACERCHAELLENGE_LINEARALGEBRA_H

#include <stdexcept>

class Tuple4 {
public:
    float x, y, z;
    const float w;
    Tuple4(float x, float y, float z, float w);
    bool operator==(const Tuple4& other) const;
    bool operator!=(const Tuple4& other) const;
    Tuple4 operator+(const Tuple4& other) const;
    Tuple4 operator-(const Tuple4& other) const;
    Tuple4 operator-() const;
};

class Point3 : public Tuple4 {
public:
    Point3();
    Point3(float x, float y, float z);
};

class Vec3: public Tuple4 {
public:
    Vec3();
    Vec3(float x, float y, float z);
};


#endif //RAYTRACERCHAELLENGE_LINEARALGEBRA_H
