//
// Created by craig on 8/8/2024.
//

#ifndef RAYTRACERCHAELLENGE_INTERSECTION_H
#define RAYTRACERCHAELLENGE_INTERSECTION_H


#include <vector>
#include <optional>

class Intersection {
public:
    float t;
    void* object;

    Intersection(float t, void* object);

    bool operator==(const Intersection& other) const;
    bool operator<(const Intersection& other) const;
    bool operator>(const Intersection& other) const;
    bool operator<=(const Intersection& other) const;
    bool operator>=(const Intersection& other) const;

    /** @return the Intersection object with the lowest positive t */
    static std::optional<Intersection> get_hit(const std::vector<Intersection> &xs);
};


#endif //RAYTRACERCHAELLENGE_INTERSECTION_H
