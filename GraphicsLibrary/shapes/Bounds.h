//
// Created by craig on 5/17/2025.
//

#ifndef RAYTRACERCHALLENGE_BOUNDS_H
#define RAYTRACERCHALLENGE_BOUNDS_H

#include "../primitives/Tuple.h"
#include <limits>
#include <algorithm>
#include <vector>

class Bounds {
    public:
        Tuple min;
        Tuple max;

        float INF = std::numeric_limits<float>::infinity();
        Bounds() :
    min(Tuple::point(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())),
    max(Tuple::point(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())) {}

        Bounds(const Tuple& min_point, const Tuple& max_point) : min(min_point), max(max_point) {}

        void include(const Tuple point) {
            min = Tuple::point(std::min(min.x, point.x),
                               std::min(min.y, point.y),
                               std::min(min.z, point.z));
            max = Tuple::point(std::max(max.x, point.x),
                               std::max(max.y, point.y),
                               std::max(max.z, point.z));
        }

        void include(const Bounds& other) {
            include(other.min);
            include(other.max);
        }

        std::vector<Tuple> corners() const {
            return {
                Tuple::point(min.x, min.y, min.z),
                Tuple::point(min.x, min.y, max.z),
                Tuple::point(min.x, max.y, min.z),
                Tuple::point(min.x, max.y, max.z),
                Tuple::point(max.x, min.y, min.z),
                Tuple::point(max.x, min.y, max.z),
                Tuple::point(max.x, max.y, min.z),
                Tuple::point(max.x, max.y, max.z),
            };
        }
};
#endif //RAYTRACERCHALLENGE_BOUNDS_H
