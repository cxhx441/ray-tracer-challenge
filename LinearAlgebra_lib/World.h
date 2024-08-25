//
// Created by craig on 8/18/2024.
//

#ifndef RAYTRACERCHAELLENGE_WORLD_H
#define RAYTRACERCHAELLENGE_WORLD_H

#include "PointLight.h"
#include "Sphere.h"
#include "PreparedComputation.h"
#include "Lighting.h"
#include "Intersection.h"

class World {
public:
    std::vector<PointLight> lights;
    std::vector<Sphere> objects;

    World() = default;
    static World DefaultWorld();

    std::vector<Intersection> intersect_world(Ray& r);
    Tuple shade_hit(PreparedComputation& precompute);
    Tuple color_at(Ray& r);
    bool is_shadowed(PointLight &l, Tuple &p);

};


#endif //RAYTRACERCHAELLENGE_WORLD_H
