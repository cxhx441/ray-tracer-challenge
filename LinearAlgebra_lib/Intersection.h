//
// Created by craig on 8/8/2024.
//

#ifndef RAYTRACERCHAELLENGE_INTERSECTION_H
#define RAYTRACERCHAELLENGE_INTERSECTION_H


#include "Sphere.h"
#include <vector>

class Intersection {
public:
    float t;
    Sphere* object;
    Intersection(float t, Sphere* object);
    bool operator==(const Intersection& other) const;
    static std::vector<Intersection> Intersect(Sphere& s, Ray& r);
    static Intersection* Hit(std::vector<Intersection> &xs);
};


#endif //RAYTRACERCHAELLENGE_INTERSECTION_H
