//
// Created by Craig Harris on 9/1/24.
//

#include "TestShape.h"

std::shared_ptr<TestShape> TestShape::create() { return std::make_shared<TestShape>(); }


Tuple TestShape::model_normal_at(const Tuple& model_point) const {
    return Tuple::vector(model_point.x, model_point.y, model_point.z);
}

std::vector<Intersection> TestShape::model_intersect(const Ray &model_ray) const {
    this->saved_ray = model_ray;
    return {};
}

Bounds TestShape::bounds() const {
    Tuple minimum = Tuple::point(-1, -1, -1);
    Tuple maximum = Tuple::point(1, 1, 1);
    return { minimum, maximum };
}
