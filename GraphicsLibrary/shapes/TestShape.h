//
// Created by Craig Harris on 9/1/24.
//

#ifndef RAYTRACERCHALLENGE_TESTSHAPE_H
#define RAYTRACERCHALLENGE_TESTSHAPE_H

#include "Shape.h"

class TestShape : public Shape{
public:
    mutable Ray saved_ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 0));

    TestShape() = default;
    ~TestShape() override = default;

    std::vector<Intersection> model_intersect(const Ray &model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
};



#endif //RAYTRACERCHALLENGE_TESTSHAPE_H
