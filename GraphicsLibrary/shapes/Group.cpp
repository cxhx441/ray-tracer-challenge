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

std::vector<Tuple> Group::bounds() const {
    // First get bounds that fit all the objects after their object space transformations
    float inf = std::numeric_limits<float>::infinity();
    float x_min = inf;
    float y_min = inf;
    float z_min = inf;
    float x_max = -inf;
    float y_max = -inf;
    float z_max = -inf;

    for (const auto &shape : children){
        auto bounds = shape->bounds();
        Tuple trans_min = shape->get_transform() * bounds[0];
        Tuple trans_max = shape->get_transform() * bounds[1];

        x_min = ( trans_min.x < x_min ) ? trans_min.x : x_min;
        y_min = ( trans_min.y < y_min ) ? trans_min.y : y_min;
        z_min = ( trans_min.z < z_min ) ? trans_min.z : z_min;

        x_max = ( trans_max.x > x_max ) ? trans_max.x : x_max;
        y_max = ( trans_max.y > y_max ) ? trans_max.y : y_max;
        z_max = ( trans_max.z > z_max ) ? trans_max.z : z_max;
    }

    // Then transform the points of this AABB into group space, and create a new AABB based off that.
    Matrix group_transform = this->get_transform();
    Tuple p00 = group_transform * Tuple::point(x_min, y_min, z_min);
    Tuple p01 = group_transform * Tuple::point(x_min, y_min, z_max);
    Tuple p02 = group_transform * Tuple::point(x_max, y_min, z_max);
    Tuple p03 = group_transform * Tuple::point(x_max, y_min, z_min);

    Tuple p10 = group_transform * Tuple::point(x_min, y_max, z_min);
    Tuple p11 = group_transform * Tuple::point(x_min, y_max, z_max);
    Tuple p12 = group_transform * Tuple::point(x_max, y_max, z_max);
    Tuple p13 = group_transform * Tuple::point(x_max, y_max, z_min);

    std::vector<float> xs = { p00.x, p01.x, p02.x, p03.x, p10.x, p11.x, p12.x, p13.x };
    std::vector<float> ys = { p00.y, p01.y, p02.y, p03.y, p10.y, p11.y, p12.y, p13.y };
    std::vector<float> zs = { p00.z, p01.z, p02.z, p03.z, p10.z, p11.z, p12.z, p13.z };

    x_min = *min_element(xs.begin(), xs.end());
    y_min = *min_element(ys.begin(), ys.end());
    z_min = *min_element(zs.begin(), zs.end());

    x_max = *max_element(xs.begin(), xs.end());
    y_max = *max_element(ys.begin(), ys.end());
    z_max = *max_element(zs.begin(), zs.end());

    Tuple minimum = Tuple::point(x_min, y_min, z_min);
    Tuple maximum = Tuple::point(x_max, y_max, z_max);

    return { minimum, maximum };
}
