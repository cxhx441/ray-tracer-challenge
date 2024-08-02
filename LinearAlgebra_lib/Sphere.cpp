//
// Created by craig on 8/2/2024.
//

#include "Sphere.h"
#include <cmath>

std::vector<float> Sphere::Intersect(Sphere &s, Ray &r) {
    /**
        Return the times t when the ray intersects the sphere
    **/
    Tuple sphere_to_ray = r.origin - Tuple::point(0, 0,0); // sphere origin is always 000 for simplicity.

    float a = Tuple::dot(r.direction, r.direction);
    float b = 2.f * Tuple::dot(r.direction, sphere_to_ray);
    float c = Tuple::dot(sphere_to_ray, sphere_to_ray) - 1;

    // Check the discriminant is valid
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return std::vector<float>(); // no intersections.

    // If it is, return both t intersections.
    float t1 = (-b - (float) sqrt(discriminant))  / ( 2 * a );
    float t2 = (-b + (float) sqrt(discriminant))  / ( 2 * a );
    return std::vector<float> {t1, t2};
}
