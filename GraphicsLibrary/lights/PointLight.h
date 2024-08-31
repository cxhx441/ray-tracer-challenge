//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_POINTLIGHT_H
#define RAYTRACERCHAELLENGE_POINTLIGHT_H

#include "../primitives/Tuple.h"

class PointLight {
public:
    Tuple point; // position
    Tuple color; // intensity

    PointLight(Tuple point, Tuple color);
};


#endif //RAYTRACERCHAELLENGE_POINTLIGHT_H
