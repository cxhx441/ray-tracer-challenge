//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_POINTLIGHT_H
#define RAYTRACERCHAELLENGE_POINTLIGHT_H

#include "../primitives/Tuple.h"
#include "../primitives/Color.h"

class PointLight {
public:
    Tuple point; // position
    Color color; // intensity

    PointLight(Tuple point, Color color);
};


#endif //RAYTRACERCHAELLENGE_POINTLIGHT_H
