//
// Created by craig on 8/2/2024.
//

#include "Ray.h"

Ray::Ray(Tuple origin, Tuple direction) {
    if (!origin.isPoint() or !direction.isVector()){
        throw std::invalid_argument("origin must be a point, direction must be a vector");
    }
    this->origin = origin;
    this->direction = direction;
}

Tuple Ray::Position(Ray &r, float t) {
    // Return the position of the point after time t.
    return r.origin + ( r.direction * t );
}
