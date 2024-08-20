//
// Created by craig on 8/8/2024.
//

#include "Intersection.h"
#include "Lighting.h"
#include <cmath>
#include <algorithm>

Intersection::Intersection(float t, Sphere* object) : t(t), object(object) {}

std::vector<Intersection> Intersection::IntersectWorld(World &w, Ray &r) {
    std::vector<Intersection> world_xs;
    for (auto& obj : w.objects){
        std::vector<Intersection> object_xs = Intersect(obj, r);
        for (auto& x : object_xs){
            world_xs.push_back(x);
        }
    }
    std::sort(world_xs.begin(), world_xs.end());
    return world_xs;
}

std::vector<Intersection> Intersection::Intersect(Sphere &s, Ray &r) {
    /**
        Return the times t when the ray intersects the sphere
    **/
    // use the sphere's inverse transformation matrix on the ray first
    Ray trans_ray = Transformation::transform( r, s.getInverseTransform() );
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
//    if (xs.empty())
//        throw std::invalid_argument("Empty Intersections Vector!");

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

bool Intersection::operator<(const Intersection& other) const { return t < other.t; }
bool Intersection::operator>(const Intersection& other) const { return t > other.t; }
bool Intersection::operator<=(const Intersection& other) const { return t <= other.t; }
bool Intersection::operator>=(const Intersection& other) const { return t >= other.t; }

Precompute Intersection::PrepareComputations(Intersection &i, Ray &r) {
    Precompute comps;
    comps.t = i.t;
    comps.object = i.object;
    comps.point = Ray::Position(r, comps.t);
    comps.eyev = -r.direction;
    comps.normalv = comps.object->NormalAt( comps.point);
    comps.inside = false;

    // if the eye is inside the object, we still want to color it correctly.
    if ( Tuple::dot(comps.eyev, comps.normalv) < 0 ){
        comps.normalv *= -1;
        comps.inside = true;
    }
    return comps;
}

Tuple Intersection::ShadeHit(World &w, Precompute &comps) {
    Tuple rendered_color(0, 0, 0, 0);
    for (auto light : w.lights){
        Tuple phong_color = Lighting::phong_lighting(comps.object->material,
                                        light,
                                        comps.point,
                                        comps.eyev,
                                        comps.normalv);
        rendered_color += phong_color;
    }

    // average lights
    rendered_color /= (float) w.lights.size();

    rendered_color.w = 1;
    return rendered_color;
}

Tuple Intersection::ColorAt(World &w, Ray &r) {
    std::vector<Intersection> xs = IntersectWorld(w, r);
    std::optional<Intersection> hit = Hit(xs);
    if (hit != std::nullopt){
        Precompute comps = PrepareComputations(*hit, r);
        Tuple rendered_color = ShadeHit(w, comps);
        return rendered_color;
    }
    return Tuple::color(0, 0, 0, 1);
}

