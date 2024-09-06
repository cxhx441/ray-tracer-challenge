//
// Created by Craig Harris on 9/5/24.
//

#ifndef RAYTRACERCHALLENGE_CYLINDER_H
#define RAYTRACERCHALLENGE_CYLINDER_H

#include "shape.h"
#include <limits>

class Cylinder : public Shape {
public:
    float minimum = -1 * std::numeric_limits<float>::infinity();
    float maximum = std::numeric_limits<float>::infinity();
    bool closed = false;

    Cylinder() = default;
    ~Cylinder() override = default;

    static Cylinder solid_glass_cylinder();

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
private:
    void intersect_caps(const Ray &r, std::vector<Intersection> &xs) const;
    static bool check_caps(const Ray &r, float t);
};


#endif //RAYTRACERCHALLENGE_CYLINDER_H
