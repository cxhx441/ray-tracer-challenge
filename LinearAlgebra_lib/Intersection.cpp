//
// Created by craig on 8/8/2024.
//

#include "Intersection.h"
#include <cmath>

Intersection::Intersection(float t, Sphere* object) : t(t), object(object) {}

std::vector<Intersection> Intersection::Intersect(Sphere &s, Ray &r) {
    /**
        Return the times t when the ray intersects the sphere
    **/
    // use the sphere's inverse transformation matrix on the ray first
    Ray trans_ray = Transformation::transform( r, Matrix::Inverse(s.transformation) );
    Tuple sphere_to_ray = trans_ray.origin - Tuple::point(0, 0,0); // sphere origin is always 000 for simplicity.

    float a = Tuple::dot(trans_ray.direction, trans_ray.direction);
    float b = 2.f * Tuple::dot(trans_ray.direction, sphere_to_ray);
    float c = Tuple::dot(sphere_to_ray, sphere_to_ray) - 1;

    // Check the discriminant is valid
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return std::vector<Intersection>(); // no intersections.

    // If it is, return both t intersections.
    float t1 = (-b - (float) sqrt(discriminant))  / ( 2 * a );
    float t2 = (-b + (float) sqrt(discriminant))  / ( 2 * a );
    return std::vector<Intersection> {Intersection(t1, &s), Intersection(t2, &s)};
}

std::optional<Intersection> Intersection::Hit(std::vector<Intersection> &xs) {
    /** return the Intersection object with the lowest positive t **/
    if (xs.empty())
        throw std::invalid_argument("Empty Intersections Vector!");

    std::optional<Intersection> nearest = std::nullopt;
    for (auto& x : xs){
        if (x.t >= 0 and (!nearest or x.t < nearest->t))
            nearest = x;
    }
    return nearest;
}

bool Intersection::operator==(const Intersection& other) const {
    if (t == other.t and object == other.object)
        return true;
    return false;
}
