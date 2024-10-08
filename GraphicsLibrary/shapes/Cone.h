//
// Created by Craig Harris on 9/6/24.
//

#ifndef RAYTRACERCHALLENGE_CONE_H
#define RAYTRACERCHALLENGE_CONE_H

#include "Shape.h"
#include <limits>

class Cone : public Shape {
public:
    float minimum = -1 * std::numeric_limits<float>::infinity();
    float maximum = std::numeric_limits<float>::infinity();
    bool closed = false; // TODO: Something is wrong with caps intersections when this is set to true.

    Cone() = default;
    ~Cone() override = default;

    static std::shared_ptr<Cone> create();
    static std::shared_ptr<Cone> solid_glass();

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
private:
    void intersect_caps(const Ray &r, std::vector<Intersection> &xs) const;
    static bool check_caps(const Ray &r, float t, float cap_radius);
};

#endif //RAYTRACERCHALLENGE_CONE_H
