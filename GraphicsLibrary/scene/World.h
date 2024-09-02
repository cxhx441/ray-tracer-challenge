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
    Color shade_hit(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_reflections=0);
    Color color_at(Ray& r, bool shadows_enabled=false, int remaining_reflections=0);
    bool is_shadowed(PointLight &l, Tuple &p);
    Color reflected_color(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_reflections=0);

};


#endif //RAYTRACERCHAELLENGE_WORLD_H
