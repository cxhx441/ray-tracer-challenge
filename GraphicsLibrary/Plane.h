//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_PLANE_H
#define RAYTRACERCHAELLENGE_PLANE_H

#include "Shape.h"

#define PLANE_EPSILON 0.00001

class Plane : public Shape{
public:
    Plane() = default;
    ~Plane() override = default;

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
};



#endif //RAYTRACERCHAELLENGE_PLANE_H
