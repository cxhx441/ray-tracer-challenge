//
// Created by Craig Harris on 7/26/24.
//

#ifndef RAYTRACERCHAELLENGE_LINEARALGEBRA_H
#define RAYTRACERCHAELLENGE_LINEARALGEBRA_H


class Tuple3 {
public:
    float x, y, z;
    Tuple3();
    Tuple3(float x, float y, float z);
    bool operator==(const Tuple3& other) const;
    bool operator!=(const Tuple3& other) const;
};

class Point3 : public Tuple3 {
public:
    const float w;
    Point3();
    Point3(float x, float y, float z);
    bool operator==(const Point3& other) const;
    bool operator!=(const Point3& other) const;
};

class Vec3: public Tuple3 {
public:
    const float w;
    Vec3();
    Vec3(float x, float y, float z);
    bool operator==(const Vec3& other) const;
    bool operator!=(const Vec3& other) const;
};


#endif //RAYTRACERCHAELLENGE_LINEARALGEBRA_H
