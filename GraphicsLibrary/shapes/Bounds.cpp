//
// Created by craig on 5/17/2025.
//

#include "Bounds.h"

// std::vector<Intersection> Bounds::model_intersect(const Ray &model_ray) const {
//     /**
//         Return the largest minimum t val and smallest maximum t val.
//     **/
//     auto [xt_min, xt_max] = check_axis(model_ray.origin.x, model_ray.direction.x);
//     if (xt_min > xt_max) return {}; // return early.
//
//     auto [yt_min, yt_max] = check_axis(model_ray.origin.y, model_ray.direction.y);
//     if (yt_min > yt_max) return {}; // return early.
//
//     auto [zt_min, zt_max] = check_axis(model_ray.origin.z, model_ray.direction.z);
//     if (zt_min > zt_max) return {}; // return early.
//
//     float t_min = std::max({xt_min, yt_min, zt_min});
//     float t_max = std::min({xt_max, yt_max, zt_max});
//
//     if (t_min > t_max)
//         return {};
//
//     return {Intersection(t_min, shared_from_this()), Intersection(t_max, shared_from_this())};
// }
//
// std::tuple<float, float> Bounds::check_axis(float origin, float direction) {
//     /**
//      * Same ray-plane intersection as in Plans class but generalized for offset planes.
//      * Handles when direction is 0 by multiplying by infinity.
//      */
//     float tmin_numerator = (-1 - origin);
//     float tmax_numerator = (1 - origin);
//
//     float tmin = -1;
//     float tmax = -1;
//     if (std::abs(direction) >= 0.00001){
//         tmin = tmin_numerator / direction;
//         tmax = tmax_numerator / direction;
//     }
//     else {
//         tmin = tmin_numerator * std::numeric_limits<float>::infinity();
//         tmax = tmax_numerator * std::numeric_limits<float>::infinity();
//     }
//
//     if ( tmin > tmax )
//         std::swap(tmin, tmax);
//
//     return {tmin, tmax};
// }

