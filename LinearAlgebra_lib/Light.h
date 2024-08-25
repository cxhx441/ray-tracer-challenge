//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_LIGHT_H
#define RAYTRACERCHAELLENGE_LIGHT_H

#include "Tuple.h"

class Light {
public:
    Tuple position;
    Tuple intensity;

    Light(Tuple position, Tuple intensity);

    static Light PointLight(Tuple position, Tuple intensity);
};


#endif //RAYTRACERCHAELLENGE_LIGHT_H
