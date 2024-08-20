//
// Created by craig on 8/18/2024.
//

#ifndef RAYTRACERCHAELLENGE_WORLD_H
#define RAYTRACERCHAELLENGE_WORLD_H

#include "Light.h"
#include "Sphere.h"

class World {
public:
    std::vector<Light> lights;
    std::vector<Sphere> objects;
    World() = default;
    static World DefaultWorld();
};


#endif //RAYTRACERCHAELLENGE_WORLD_H
