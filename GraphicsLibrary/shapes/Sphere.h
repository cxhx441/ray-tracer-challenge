//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_SPHERE_H
#define RAYTRACERCHAELLENGE_SPHERE_H

#include "Shape.h"

class Sphere : public Shape{
public:
    Sphere() = default;
    ~Sphere() override = default;

    static std::shared_ptr<Sphere> create();
    static std::shared_ptr<Sphere> solid_glass();

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
};



#endif //RAYTRACERCHAELLENGE_SPHERE_H
