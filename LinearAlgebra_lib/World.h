//
// Created by craig on 8/18/2024.
//

#ifndef RAYTRACERCHAELLENGE_WORLD_H
#define RAYTRACERCHAELLENGE_WORLD_H

#include "Light.h"
#include "Sphere.h"
#include "PreparedComputation.h"
#include "Lighting.h"
#include "Intersection.h"

class World {
public:
    std::vector<Light> lights;
    std::vector<Sphere> objects;

    World() = default;
    static World DefaultWorld();

    std::vector<Intersection> IntersectWorld(Ray& r);
    Tuple ShadeHit(PreparedComputation& precompute);
    Tuple ColorAt(Ray& r);
    bool IsShadowed(Light &l, Tuple &p);

};


#endif //RAYTRACERCHAELLENGE_WORLD_H
