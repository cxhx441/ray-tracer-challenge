//
// Created by Craig Harris on 9/5/24.
//

#include "Cylinder.h"

Cylinder Cylinder::solid_glass_cylinder() {
    Cylinder c;
    c.material.color = Color::black();
    c.material.transparency = 1;
    c.material.refractive_index = Material::RefractiveIndices::glass;
    c.material.reflective = 1;
    c.material.diffuse = 0.1;
    c.material.ambient = 0.1;
    c.material.specular = 1;
    c.material.shininess = 300;

    return c;
}

Tuple Cylinder::model_normal_at(const Tuple &model_point) const {
    return {model_point.x, 0, model_point.z, 0};
}

std::vector<Intersection> Cylinder::model_intersect(const Ray &model_ray) const {
    /**
        Return the times t when the ray intersects the infinitely long vertical cylinder.
    **/
//    Tuple sphere_to_ray = model_ray.origin - Tuple::point(0, 0,0); // sphere origin is always 000 for simplicity.
    float a = pow(model_ray.direction.x, 2) +
              pow(model_ray.direction.z, 2);

    if ( abs(a) < 0.001 ) // ray is parallel.
        return {};

    float b = 2. * model_ray.origin.x * model_ray.direction.x +
              2. * model_ray.origin.z * model_ray.direction.z;

    float c = pow(model_ray.origin.x, 2) +
              pow(model_ray.origin.z, 2) -
              1;

    // Check the discriminant is valid
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return {}; // no intersections.

    // If it is, return both t intersections.
    float t0 = (-b - (float) sqrt(discriminant))  / ( 2 * a );
    float t1 = (-b + (float) sqrt(discriminant))  / ( 2 * a );

    std::vector<Intersection> xs {};
    float y0 = model_ray.origin.y + t0 * model_ray.direction.y;
    if (minimum_y < y0 && y0 < maximum_y)
        xs.push_back(Intersection(t0, (void*) this));

    float y1 = model_ray.origin.y + t1 * model_ray.direction.y;
    if (minimum_y < y1 && y1 < maximum_y)
        xs.push_back(Intersection(t1, (void*) this));

    return xs;
}

