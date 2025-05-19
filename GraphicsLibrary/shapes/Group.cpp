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

    Bounds child_bounds = child->bounds(); // In object space
    for (const auto& corner : child_bounds.corners()) {
        Tuple transformed_corner = child->get_transform() * corner;
        group_bounds.include(transformed_corner);
    }
}

std::vector<Intersection> Group::model_intersect(const Ray &model_ray) const {
    // Ray group_ray = Transformation::transform( model_ray, this->get_inverse_transform() );
    if ( this->bounds_intersect(model_ray).empty() ) {
        // check if ray misses bounding box
        return {};
    }

    std::vector<Intersection> group_xs = {};
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

std::vector<Intersection> Group::bounds_intersect(const Ray &model_ray) const {
    /**
        Return the largest minimum t val and smallest maximum t val.
    **/

    auto [xt_min, xt_max] = check_bounds_axis(model_ray.origin.x, model_ray.direction.x, group_bounds.min.x, group_bounds.max.x);
    if (xt_min > xt_max) return {}; // return early.

    auto [yt_min, yt_max] = check_bounds_axis(model_ray.origin.y, model_ray.direction.y, group_bounds.min.y, group_bounds.max.y);
    if (yt_min > yt_max) return {}; // return early.

    auto [zt_min, zt_max] = check_bounds_axis(model_ray.origin.z, model_ray.direction.z, group_bounds.min.z, group_bounds.max.z);
    if (zt_min > zt_max) return {}; // return early.

    float t_min = std::max({xt_min, yt_min, zt_min});
    float t_max = std::min({xt_max, yt_max, zt_max});

    if (t_min > t_max)
        return {};

    return {Intersection(t_min, shared_from_this()), Intersection(t_max, shared_from_this())};
}

std::tuple<float, float> Group::check_bounds_axis(float origin, float direction, float bound_min, float bound_max) const {
    /**
     * Same ray-plane intersection as in Plans class but generalized for offset planes.
     * Handles when direction is 0 by multiplying by infinity.
     */
    float tmin_numerator = (bound_min - origin);
    float tmax_numerator = (bound_max - origin);

    float tmin;
    float tmax;
    if (std::abs(direction) >= 0.00001){
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    }
    else {
        tmin = tmin_numerator * std::numeric_limits<float>::infinity();
        tmax = tmax_numerator * std::numeric_limits<float>::infinity();
    }

    if ( tmin > tmax )
        std::swap(tmin, tmax);

    return {tmin, tmax};
}

void Group::update_bounds(){
    for (const auto &child_shape : children){
        // auto shape_xs = shape->intersect(model_ray);
        Bounds child_bounds = child_shape->bounds(); // In object space
        for (const auto& corner : child_bounds.corners()) {
            Tuple transformed_corner = child_shape->get_transform() * corner;
            group_bounds.include(transformed_corner);
        }
    }
}

Bounds Group::bounds() const {
    return group_bounds;
}
