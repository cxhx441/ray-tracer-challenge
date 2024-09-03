//
// Created by craig on 8/18/2024.
//

#include "World.h"
#include <algorithm>
#include <cmath>

World World::DefaultWorld() {
    World w;
    PointLight l(Tuple::point(-10, 10, -10), Color::white() );
    w.lights.push_back(l);

    // Unit sphere at origin.
    Sphere s1;
    s1.name = std::string("s1");
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    // Half unit sphere at origin.
    Sphere s2;
    s2.name = std::string("s2");
    s2.set_transform(Transformation::scaling(0.5));

    w.spheres.push_back(s1);
    w.spheres.push_back(s2);
    return w;
}

std::vector<Intersection> World::intersect_world(Ray &r) {
    std::vector<Intersection> world_xs;
    // Iterate over Spheres.
    for (auto& sphere : spheres){
        std::vector<Intersection> object_xs = sphere.intersect(r);
        for (auto& x : object_xs){
            world_xs.push_back(x);
        }
    }

    // Iterate over Planes.
    for (auto& plane : planes){
        std::vector<Intersection> object_xs = plane.intersect(r);
        for (auto& x : object_xs){
            world_xs.push_back(x);
        }
    }

    std::sort(world_xs.begin(), world_xs.end());
    return world_xs;
}

Color World::shade_hit(PreparedComputation &precompute, bool shadows_enabled, int remaining_rays) {
    Color surface_color(0, 0, 0, 0);
    for (auto light : lights){
        bool shadowed = shadows_enabled && is_shadowed(light, precompute.over_point);
        Color phong_color = LightingModels::phong_lighting(precompute.object->material,
                                                           *precompute.object,
                                                           light,
                                                           precompute.point,
                                                           precompute.eyev,
                                                           precompute.normalv,
                                                           shadowed
                                                     );
        surface_color += phong_color;
    }
    // average lights
    surface_color /= (float) lights.size();

    Color reflected_col = reflected_color(precompute, shadows_enabled, remaining_rays);
    Color refracted_col = refracted_color(precompute, shadows_enabled, remaining_rays);
    Material material = precompute.object->material;
    Color rendered_color(0, 0, 0, 0);
    if ( material.reflective > 0 && material.transparency > 0 ){
        float reflectance = schlick_reflectance(precompute);
        rendered_color = surface_color + (reflected_col * reflectance) + (refracted_col * (1 - reflectance));
    }
    else
        rendered_color = surface_color + reflected_col + refracted_col;

    rendered_color.a = 1;
    return rendered_color;
}

Color World::color_at(Ray &r, bool shadows_enabled, int remaining_rays) {
    std::vector<Intersection> xs = intersect_world(r);
    std::optional<Intersection> hit = Intersection::get_hit(xs);
    if (hit != std::nullopt){
        auto comps = PreparedComputation(*hit, r, xs);
        Color rendered_color = shade_hit(comps, shadows_enabled, remaining_rays);
        return rendered_color;
    }
    return Color::black();
}

bool World::is_shadowed(PointLight &l, Tuple &p) {
    Tuple p_to_light = l.point - p;
    float distance = p_to_light.magnitude();
    Tuple direction = Tuple::normalized(p_to_light);
    Ray r(p, direction);
    std::vector<Intersection> xs = intersect_world(r);
    std::optional<Intersection> hit = Intersection::get_hit(xs);
    if (hit != std::nullopt && hit->t < distance)
        return true;
    return false;
}

Color World::reflected_color(PreparedComputation &precompute, bool shadows_enabled, int remaining_reflections) {
    if (precompute.object->material.reflective == 0 || remaining_reflections <= 0)
        return Color::black();

    Ray reflected_ray(precompute.over_point, precompute.reflectv);
    Color color = color_at(reflected_ray, shadows_enabled, remaining_reflections-1);
    Color ref_color = color * precompute.object->material.reflective;
    ref_color.a = 1;
    return ref_color;
}

Color World::refracted_color(PreparedComputation &precompute, bool shadows_enabled, int remaining_refractions) {
    if (precompute.object->material.transparency == 0 || remaining_refractions <= 0)
        return Color::black();

    // check for total internal reflection sin(theta_i) / sin(theta_t) = n2 / n1 ---> i is incoming ray, t is refracted
    float n_ratio = precompute.n1 / precompute.n2;
    float cos_i = Tuple::dot(precompute.eyev, precompute.normalv ); // cos(theta_i) same as dot()
    float sin2_t = powf(n_ratio, 2) * (1 - powf(cos_i, 2)); // trig
    if ( sin2_t > 1.f ) // total internal reflection
        return Color::black();

    // otherwise get refracted ray
    float cos_t = sqrtf(1.0f - sin2_t); // trig identity
    Tuple refracted_direction = precompute.normalv * (n_ratio * cos_i - cos_t) - precompute.eyev * n_ratio;
    Ray refracted_ray = Ray(precompute.under_point, refracted_direction);
    Color color = color_at(refracted_ray, shadows_enabled, remaining_refractions - 1);
    Color refracted_color = color * precompute.object->material.transparency;
    refracted_color.a = 1;
    return refracted_color;



//    Ray refracted_ray(precompute.under_point, precompute.);
//    Color color = color_at(reflected_ray, shadows_enabled, remaining_reflections-1);
//    Color ref_color = color * precompute.object->material.reflective;
//    ref_color.a = 1;
    return Color::white();
}

float World::schlick_reflectance(PreparedComputation &precompute) {
    float n1 = precompute.n1;
    float n2 = precompute.n2;

    float cos = Tuple::dot(precompute.eyev, precompute.normalv);

    // total internal reflection can only occur if n1 > n2
    if ( n1 > n2 ){
        float n_ratio = n1 / n2;
        float sin2_t = powf(n_ratio, 2) * (1 - powf(cos, 2)); // trig
        if ( sin2_t > 1.0 )
            return 1.0;

        float cos_t = sqrtf(1.0f - sin2_t); // trig identity

        // when n1 > n2, use cos(theta_t) instead
        cos = cos_t;
    }
    float r0 = powf((n1 - n2) / (n1 + n2), 2);
    return r0 + (1 - r0) * powf(1 - cos, 5);
}

