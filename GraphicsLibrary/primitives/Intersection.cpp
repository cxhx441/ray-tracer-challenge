//
// Created by craig on 8/8/2024.
//

#include "Intersection.h"

Intersection::Intersection(float t, void* object) : t(t), object(object) {}

bool Intersection::operator==(const Intersection& other) const {
    if (t == other.t and object == other.object)
        return true;
    return false;
}

bool Intersection::operator<(const Intersection& other) const { return t < other.t; }
bool Intersection::operator>(const Intersection& other) const { return t > other.t; }
bool Intersection::operator<=(const Intersection& other) const { return t <= other.t; }
bool Intersection::operator>=(const Intersection& other) const { return t >= other.t; }

std::optional<Intersection> Intersection::get_hit(std::vector<Intersection> &xs) {
    std::optional<Intersection> nearest = std::nullopt;
    for (auto& x : xs){
        if (x.t >= 0 and (!nearest or x.t < nearest->t))
            nearest = x;
    }
    return nearest;
}



