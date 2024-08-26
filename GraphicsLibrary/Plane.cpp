//
// Created by craig on 8/2/2024.
//

#include "Plane.h"

Tuple Plane::model_normal_at(const Tuple &model_point) const {
    return Tuple::vector(0, 1, 0);
}

std::vector<Intersection> Plane::model_intersect(const Ray &model_ray) const {
    /**
        Return the time t when the ray intersects the plane.
    **/
    if (std::abs(model_ray.direction.y) < PLANE_EPSILON){
        return {};
    }
    float t = -model_ray.origin.y / model_ray.direction.y;
    return {Intersection(t, (void *) this)};
}
