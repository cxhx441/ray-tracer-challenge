//
// Created by Craig Harris on 9/6/24.
//

#include "Cone.h"
#include <cmath>

std::shared_ptr<Cone> Cone::create() { return std::make_shared<Cone>(); }

std::shared_ptr<Cone> Cone::solid_glass() {
    auto c = std::make_shared<Cone>();
    c->material.color = Color::black();
    c->material.transparency = 1;
    c->material.refractive_index = Material::RefractiveIndices::glass;
    c->material.reflective = 1;
    c->material.diffuse = 0.1;
    c->material.ambient = 0.1;
    c->material.specular = 1;
    c->material.shininess = 300;

    return c;
}

Tuple Cone::model_normal_at(const Tuple &model_point) const {
    // for caps
    float dist = pow(model_point.x, 2) + pow(model_point.z, 2);
    if (dist < 1 && model_point.y >= (maximum - 0.001))
        return {0, 1, 0, 0};
    else if (dist < 1 && model_point.y <= (minimum + 0.001))
        return {0, -1, 0, 0};


    // for non-caps
    float y = sqrtf(
            powf(model_point.x, 2) +
            powf(model_point.z, 2)
    );
    y = model_point.y > 0 ? -y : y;

    return Tuple::vector(model_point.x, y, model_point.z);
}

std::vector<Intersection> Cone::model_intersect(const Ray &model_ray) const {
    /**
        Return the times t when the ray intersects the infinitely long vertical cones.
    **/
    std::vector<Intersection> xs {};

    float a = pow(model_ray.direction.x, 2) -
              pow(model_ray.direction.y, 2) +
              pow(model_ray.direction.z, 2);

    float b = 2. * model_ray.origin.x * model_ray.direction.x -
              2. * model_ray.origin.y * model_ray.direction.y +
              2. * model_ray.origin.z * model_ray.direction.z;

    float c = pow(model_ray.origin.x, 2) -
              pow(model_ray.origin.y, 2) +
              pow(model_ray.origin.z, 2);

    // ray is parallel to one cone but hits the other
    if ( std::abs(a) < 0.001 && std::abs(b) > 0.001) {
        xs.push_back({-c/(2.f*b), shared_from_this()});
        intersect_caps(model_ray, xs);
        return xs;
    }

    // ray misses both cones.
    if ( std::abs(a) < 0.001){
        return {};
    }



    // Check the discriminant is valid
    double discriminant = (b * b) - (4 * a * c);
    if (fabs(discriminant) < 0.001)
        discriminant = 0;
    if (discriminant < 0)
        return {}; // no intersections.

    // If it is, return both t intersections.
    float t0 = (-b - (float) sqrt(discriminant))  / ( 2 * a );
    float t1 = (-b + (float) sqrt(discriminant))  / ( 2 * a );
    if (t0 > t1){
        std::swap(t0, t1);
    }

    float y0 = model_ray.origin.y + t0 * model_ray.direction.y;
    if (minimum < y0 && y0 < maximum)
        xs.push_back(Intersection(t0, shared_from_this()));

    float y1 = model_ray.origin.y + t1 * model_ray.direction.y;
    if (minimum < y1 && y1 < maximum)
        xs.push_back(Intersection(t1, shared_from_this()));

    intersect_caps(model_ray, xs);

    return xs;
}

void Cone::intersect_caps(const Ray &r, std::vector<Intersection> &xs) const {
    if (!closed || std::fabs(r.direction.y) < 0.001)
        return;

    // check intersection with lower cap
    float t_min = (minimum - r.origin.y) / r.direction.y;
    if (check_caps(r, t_min, std::fabs(minimum)))
        xs.push_back({t_min, shared_from_this()});

    // check intersection with higher cap
    float t_max = (maximum - r.origin.y) / r.direction.y;
    if (check_caps(r, t_max, std::fabs(maximum)))
        xs.push_back({t_max, shared_from_this()});
}

bool Cone::check_caps(const Ray &r, float t, float cap_radius) {
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;
    return pow(x, 2) + pow(z, 2) - cap_radius < 0.001;
}


