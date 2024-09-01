//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_RAY_H
#define RAYTRACERCHAELLENGE_RAY_H

#include "Tuple.h"

class Ray {
public:
    Tuple origin;
    Tuple direction;

    Ray(Tuple origin, Tuple direction);

    /** @Return the point of the Ray after time time. */
    static Tuple position(Ray& r, float time);
};


#endif //RAYTRACERCHAELLENGE_RAY_H
