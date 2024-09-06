//
// Created by craig on 9/5/2024.
//

#ifndef RAYTRACERCHALLENGE_CUBE_H
#define RAYTRACERCHALLENGE_CUBE_H


#include "Shape.h"

class Cube : public Shape {
public:
    Cube() = default;
    ~Cube() override = default;

    static Cube solid_glass_cube();

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
private:
    static std::tuple<float, float> check_axis(float origin, float direction);
};


#endif //RAYTRACERCHALLENGE_CUBE_H
