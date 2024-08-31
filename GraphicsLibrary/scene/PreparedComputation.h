//
// Created by Craig Harris on 8/25/24.
//

#ifndef RAYTRACERCHAELLENGE_PREPAREDCOMPUTATION_H
#define RAYTRACERCHAELLENGE_PREPAREDCOMPUTATION_H

#include "../shapes/Sphere.h"
#include "../primitives/Intersection.h"

class PreparedComputation{
public:
    float t = 0;
    Sphere* object = nullptr;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
    Tuple over_point;

    PreparedComputation(Intersection &i, Ray &r);
    ~PreparedComputation() = default;
};

#endif //RAYTRACERCHAELLENGE_PREPAREDCOMPUTATION_H
