//
// Created by craig on 9/11/2024.
//

#ifndef RAYTRACERCHALLENGE_GROUP_H
#define RAYTRACERCHALLENGE_GROUP_H

#include "Shape.h"

class Group : public Shape{
public:
    std::vector<std::shared_ptr<Shape>> children = {};

    static std::shared_ptr<Group> create();

    Group() = default;
    ~Group() override = default;

    void add_child(const std::shared_ptr<Shape> &child);

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;

};


#endif //RAYTRACERCHALLENGE_GROUP_H
