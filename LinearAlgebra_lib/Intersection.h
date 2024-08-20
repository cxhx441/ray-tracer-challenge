//
// Created by craig on 8/8/2024.
//

#ifndef RAYTRACERCHAELLENGE_INTERSECTION_H
#define RAYTRACERCHAELLENGE_INTERSECTION_H


#include "Sphere.h"
#include "World.h"
#include <vector>
#include <optional>

struct Precompute{
    float t = 0;
    Sphere* object = nullptr;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
};


class Intersection {
public:
    float t;
    Sphere* object;
    Intersection(float t, Sphere* object);
    bool operator==(const Intersection& other) const;
    bool operator<(const Intersection& other) const;
    bool operator>(const Intersection& other) const;
    bool operator<=(const Intersection& other) const;
    bool operator>=(const Intersection& other) const;
    static Precompute PrepareComputations(Intersection& i , Ray& r);
    static std::vector<Intersection> IntersectWorld(World& w, Ray& r);
    static std::vector<Intersection> Intersect(Sphere& s, Ray& r);
    static std::optional<Intersection> Hit(std::vector<Intersection> &xs);
    static Tuple ShadeHit(World& w, Precompute& precompute);
    static Tuple ColorAt(World& w, Ray& r);
};


#endif //RAYTRACERCHAELLENGE_INTERSECTION_H
