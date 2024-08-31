//
// Created by craig on 8/18/2024.
//

#ifndef RAYTRACERCHAELLENGE_WORLD_H
#define RAYTRACERCHAELLENGE_WORLD_H

#include "../lights/PointLight.h"
#include "../shapes/Sphere.h"
#include "../shapes/Plane.h"
#include "PreparedComputation.h"
#include "LightingModels.h"
#include "../primitives/Intersection.h"

class World {
public:
    std::vector<PointLight> lights;
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;

    World() = default;
    static World DefaultWorld();

    std::vector<Intersection> intersect_world(Ray& r);
    Tuple shade_hit(PreparedComputation& precompute);
    Tuple color_at(Ray& r);
    bool is_shadowed(PointLight &l, Tuple &p);

};


#endif //RAYTRACERCHAELLENGE_WORLD_H
