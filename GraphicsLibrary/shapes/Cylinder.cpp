//
// Created by Craig Harris on 9/5/24.
//

#include "Cylinder.h"
#include <cmath>

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
    // for caps
    float dist = pow(model_point.x, 2) + pow(model_point.z, 2);
    if (dist < 1 && model_point.y >= (maximum - 0.001))
        return {0, 1, 0, 0};
    else if (dist < 1 && model_point.y <= (minimum + 0.001))
        return {0, -1, 0, 0};

    return {model_point.x, 0, model_point.z, 0};
}

std::vector<Intersection> Cylinder::model_intersect(const Ray &model_ray) const {
    /**
        Return the times t when the ray intersects the infinitely long vertical cylinder.
    **/
//    Tuple sphere_to_ray = model_ray.origin - Tuple::point(0, 0,0); // sphere origin is always 000 for simplicity.
    std::vector<Intersection> xs {};

    float a = pow(model_ray.direction.x, 2) +
              pow(model_ray.direction.z, 2);

    if ( std::abs(a) < 0.001 ) {// ray is parallel.
        intersect_caps(model_ray, xs);
        return xs;
    }

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

    float y0 = model_ray.origin.y + t0 * model_ray.direction.y;
    if (minimum < y0 && y0 < maximum)
        xs.push_back(Intersection(t0, (void*) this));

    float y1 = model_ray.origin.y + t1 * model_ray.direction.y;
    if (minimum < y1 && y1 < maximum)
        xs.push_back(Intersection(t1, (void*) this));

    intersect_caps(model_ray, xs);

    return xs;
}

void Cylinder::intersect_caps(const Ray &r, std::vector<Intersection> &xs) const {
    if (!closed || std::abs(r.direction.y) < 0.0001)
        return;

    // check intersection with lower cap
    float t_min = (minimum - r.origin.y) / r.direction.y;
    if (check_caps(r, t_min))
        xs.push_back({t_min, (void*) this});

    // check intersection with higher cap
    float t_max = (maximum - r.origin.y) / r.direction.y;
    if (check_caps(r, t_max))
        xs.push_back({t_max, (void*) this});
}

bool Cylinder::check_caps(const Ray &r, float t) {
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;
//    return pow(x, 2) + pow(z, 2) <= 1;
    return pow(x, 2) + pow(z, 2) - 1 < 0.000001;
}


