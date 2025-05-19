//
// Created by craig on 9/11/2024.
//

#ifndef RAYTRACERCHALLENGE_GROUP_H
#define RAYTRACERCHALLENGE_GROUP_H

#include "Shape.h"
#include "Bounds.h"

class Group : public Shape{
public:
    std::vector<std::shared_ptr<Shape>> children = {};
    Bounds group_bounds;

    static std::shared_ptr<Group> create();

    Group() = default;
    ~Group() override = default;

    void add_child(const std::shared_ptr<Shape> &child);


    void update_bounds();
    Bounds bounds() const override;
    // Bounds update_bounds() const;
    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
    std::vector<Intersection> bounds_intersect(const Ray &model_ray) const;
    std::tuple<float, float> check_bounds_axis(float origin, float direction, float bound_min, float bound_max) const;

};


#endif //RAYTRACERCHALLENGE_GROUP_H
