//
// Created by craig on 8/18/2024.
//

#ifndef RAYTRACERCHAELLENGE_WORLD_H
#define RAYTRACERCHAELLENGE_WORLD_H

#include "Light.h"
#include "Sphere.h"

class World {
public:
    Light light;
    std::vector<Sphere> objects;
    World();

    static World DefaultWorld();
};


#endif //RAYTRACERCHAELLENGE_WORLD_H
