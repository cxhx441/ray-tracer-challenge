//
// Created by craig on 9/11/2024.
//

#include "Group.h"
#include <algorithm>

std::shared_ptr<Group> Group::create() {
    return std::make_shared<Group>();
}

void Group::add_child(const std::shared_ptr<Shape> &child) {
    children.push_back(child);
    child->parent = shared_from_this();
}

std::vector<Intersection> Group::model_intersect(const Ray &model_ray) const {
    std::vector<Intersection> group_xs = {};
    // Ray group_ray = Transformation::transform( model_ray, this->get_inverse_transform() );
    for (const auto &shape : children){
        auto shape_xs = shape->intersect(model_ray);
        group_xs.insert(group_xs.end(), shape_xs.begin(), shape_xs.end());
    }
    std::sort(group_xs.begin(), group_xs.end());
    return group_xs;
}

Tuple Group::model_normal_at(const Tuple &model_point) const {
    throw std::runtime_error("This is not implemented and should never be called");
}

