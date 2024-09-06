//
// Created by craig on 9/5/2024.
//

#include <limits>
#include <algorithm>
#include "Cube.h"

Cube Cube::solid_glass_cube() {
    Cube c;
    c.material.color = Color::black();
    c.material.transparency = 1;
    c.material.refractive_index = Material::RefractiveIndices::glass;
    c.material.reflective = 1;
    c.material.diffuse = 0.1;
    c.material.ambient = 0.1;
    c.material.specular = 1;
    c.material.shininess = 300;

    return c;
}

Tuple Cube::model_normal_at(const Tuple &model_point) const {
    /**
     *  The normal would typically be on the corresponding face of the component whose abs_val is 1. But we can't trust
     *  == due to floating point, so just pick the one with the largest abs_val.
     */
    float abs_x = std::abs(model_point.x);
    float abs_y = std::abs(model_point.y);
    float abs_z = std::abs(model_point.z);

    if (abs_x >= abs_y && abs_x >= abs_z)
        return Tuple::vector(model_point.x, 0, 0);
    else if (abs_y >= abs_x && abs_y >= abs_z)
        return Tuple::vector(0, model_point.y, 0);
    else
        return Tuple::vector(0, 0, model_point.z);
}

std::vector<Intersection> Cube::model_intersect(const Ray &model_ray) const {
    /**
        Return the largest minimum t val and smallest maximum t val.
    **/
    auto [xt_min, xt_max] = check_axis(model_ray.origin.x, model_ray.direction.x);
    if (xt_min > xt_max) return {}; // return early.

    auto [yt_min, yt_max] = check_axis(model_ray.origin.y, model_ray.direction.y);
    if (yt_min > yt_max) return {}; // return early.

    auto [zt_min, zt_max] = check_axis(model_ray.origin.z, model_ray.direction.z);
    if (zt_min > zt_max) return {}; // return early.

    float t_min = std::max({xt_min, yt_min, zt_min});
    float t_max = std::min({xt_max, yt_max, zt_max});

    if (t_min > t_max)
        return {};

    return {Intersection(t_min, (void *) this), Intersection(t_max, (void *) this)};
}

std::tuple<float, float> Cube::check_axis(float origin, float direction) {
    /**
     * Same ray-plane intersection as in Plans class but generalized for offset planes.
     * Handles when direction is 0 by multiplying by infinity.
     */
    float tmin_numerator = (-1 - origin);
    float tmax_numerator = (1 - origin);

    float tmin = -1;
    float tmax = -1;
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

