//
// Created by craig on 8/8/2024.
//

#include "Intersection.h"

Intersection::Intersection(float t, std::shared_ptr<const Shape> shape) : t(t), shape(std::move(shape)) {}

bool Intersection::operator==(const Intersection& other) const {
    if (t == other.t and shape == other.shape)
        return true;
    return false;
}

bool Intersection::operator<(const Intersection& other) const { return t < other.t; }
bool Intersection::operator>(const Intersection& other) const { return t > other.t; }
bool Intersection::operator<=(const Intersection& other) const { return t <= other.t; }
bool Intersection::operator>=(const Intersection& other) const { return t >= other.t; }

std::optional<Intersection> Intersection::get_hit(const std::vector<Intersection> &xs) {
    std::optional<Intersection> nearest = std::nullopt;
    for (auto& x : xs){
        if (x.t >= 0 and (!nearest or x.t < nearest->t))
            nearest = x;
    }
    return nearest;
}



