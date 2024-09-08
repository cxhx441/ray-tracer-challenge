//
// Created by craig on 8/2/2024.
//

#include "Sphere.h"
#include <cmath>
#include <utility>

Sphere Sphere::solid_glass_sphere() {
    Sphere s;
    s.material.color = Color::black();
    s.material.transparency = 1;
    s.material.refractive_index = Material::RefractiveIndices::glass;
    s.material.reflective = 1;
    s.material.diffuse = 0.1;
    s.material.ambient = 0.1;
    s.material.specular = 1;
    s.material.shininess = 300;

    return s;
}

Tuple Sphere::model_normal_at(const Tuple &model_point) const {
    return model_point - Tuple::point(0, 0, 0);
}
std::vector<Intersection> Sphere::model_intersect(const Ray &model_ray) const {
    /**
        Return the times t when the ray intersects the sphere.
    **/
    Tuple sphere_to_ray = model_ray.origin - Tuple::point(0, 0,0); // sphere origin is always 000 for simplicity.

    float a = Tuple::dot(model_ray.direction, model_ray.direction);
    float b = 2.f * Tuple::dot(model_ray.direction, sphere_to_ray);
    float c = Tuple::dot(sphere_to_ray, sphere_to_ray) - 1;

    // Check the discriminant is valid
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return {}; // no intersections.

    // If it is, return both t intersections.
    float t1 = (-b - (float) sqrt(discriminant))  / ( 2 * a );
    float t2 = (-b + (float) sqrt(discriminant))  / ( 2 * a );
    return {Intersection(t1, std::make_shared<Sphere>(*this)), Intersection(t2, std::make_shared<Sphere>(*this))};
}

