//
// Created by craig on 5/17/2025.
//

#ifndef RAYTRACERCHALLENGE_BOUNDS_H
#define RAYTRACERCHALLENGE_BOUND_H


#include "Shape.h"

class Bounds : public Shape {
public:
    static std::shared_ptr<Bounds> create();
    Tuple minimum_point = Tuple::point(0, 0, 0);
    Tuple maximum_point = Tuple::point(0, 0, 0);

    Bounds() = default;
    ~Bounds() override = default;

    // std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    // Tuple model_normal_at(const Tuple& model_point) const override;
// private:
//     static std::tuple<float, float> check_axis(float origin, float direction);
// };
//

#endif //RAYTRACERCHALLENGE_BOUNDS_H
