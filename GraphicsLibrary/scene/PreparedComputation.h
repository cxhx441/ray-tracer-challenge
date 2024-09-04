//
// Created by Craig Harris on 8/25/24.
//

#ifndef RAYTRACERCHAELLENGE_PREPAREDCOMPUTATION_H
#define RAYTRACERCHAELLENGE_PREPAREDCOMPUTATION_H

#include "../shapes/Sphere.h"
#include "../primitives/Intersection.h"

#define SHADOW_EPSILON 0.001
#define REFRACTION_EPSILON 0.001

class PreparedComputation{
private:
    void set_refraction_details( Intersection &hit, const std::vector<Intersection> &xs );
public:
    float t = 0;
    Sphere* object = nullptr;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    Tuple reflectv;
    bool inside;
    Tuple over_point;
    Tuple under_point;
    float n1, n2; // refractive indices of the material being exited, entered.

    PreparedComputation(Intersection &hit, Ray &r, const std::vector<Intersection> &xs);
    ~PreparedComputation() = default;
};

#endif //RAYTRACERCHAELLENGE_PREPAREDCOMPUTATION_H
