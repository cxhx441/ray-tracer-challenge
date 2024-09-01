//
// Created by Craig Harris on 9/1/24.
//

#include "TestShape.h"

Tuple TestShape::model_normal_at(const Tuple& model_point) const {
    return Tuple::vector(model_point.x, model_point.y, model_point.z);
}

std::vector<Intersection> TestShape::model_intersect(const Ray &model_ray) const {
    this->saved_ray = model_ray;
    return {};
}
