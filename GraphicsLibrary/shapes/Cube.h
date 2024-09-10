//
// Created by craig on 9/5/2024.
//

#ifndef RAYTRACERCHALLENGE_CUBE_H
#define RAYTRACERCHALLENGE_CUBE_H


#include "Shape.h"

class Cube : public Shape {
public:
    static std::shared_ptr<Cube> create();
    static std::shared_ptr<Cube> solid_glass();

    Cube() = default;
    ~Cube() override = default;

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
private:
    static std::tuple<float, float> check_axis(float origin, float direction);
};


#endif //RAYTRACERCHALLENGE_CUBE_H
