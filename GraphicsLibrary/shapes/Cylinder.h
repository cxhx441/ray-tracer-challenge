//
// Created by Craig Harris on 9/5/24.
//

#ifndef RAYTRACERCHALLENGE_CYLINDER_H
#define RAYTRACERCHALLENGE_CYLINDER_H

#include "shape.h"
#include <limits.h>

class Cylinder : public Shape {
public:
    float minimum_y = -1 * std::numeric_limits<float>::infinity();
    float maximum_y = std::numeric_limits<float>::infinity();

    Cylinder() = default;
    ~Cylinder() override = default;

    static Cylinder solid_glass_cylinder();

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
};


#endif //RAYTRACERCHALLENGE_CYLINDER_H
