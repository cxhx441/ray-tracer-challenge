//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_SPHERE_H
#define RAYTRACERCHAELLENGE_SPHERE_H

#include "Ray.h"
#include <vector>

class Sphere {
public:
    Sphere() = default;
    static std::vector<float> Intersect(Sphere& s, Ray& r);
};


#endif //RAYTRACERCHAELLENGE_SPHERE_H
