//
// Created by craig on 8/18/2024.
//

#include "World.h"

World World::DefaultWorld() {
    World w;
    Light l = Light::PointLight(Tuple::point(-10, 10, -10), Tuple::color(1, 1, 1, 1) );
    w.lights.push_back(l);

    // Unit sphere at origin.
    Sphere s1;
    s1.material.color = Tuple::color(0.8, 1.0, 0.6, 1);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    // Half unit sphere at origin.
    Sphere s2;
    s2.setTransform(Transformation::scaling(0.5));

    w.objects.push_back(s1);
    w.objects.push_back(s2);
    return w;
}

std::vector<Intersection> World::IntersectWorld(Ray &r) {
    std::vector<Intersection> world_xs;
    for (auto& sphere : objects){
        std::vector<Intersection> object_xs = sphere.Intersect(r);
        for (auto& x : object_xs){
            world_xs.push_back(x);
        }
    }
    std::sort(world_xs.begin(), world_xs.end());
    return world_xs;
}

Tuple World::ShadeHit(PreparedComputation &comps) {
    Tuple rendered_color(0, 0, 0, 0);
    for (auto light : lights){
        bool is_shadowed = IsShadowed(light, comps.over_point);
        Tuple phong_color = Lighting::phong_lighting(comps.object->material,
                                                     light,
                                                     comps.point,
                                                     comps.eyev,
                                                     comps.normalv, is_shadowed);
        rendered_color += phong_color;
    }

    // average lights
    rendered_color /= (float) lights.size();

    rendered_color.w = 1;
    return rendered_color;
}

Tuple World::ColorAt(Ray &r) {
    std::vector<Intersection> xs = IntersectWorld(r);
    std::optional<Intersection> hit = Intersection::Hit(xs);
    if (hit != std::nullopt){
        auto comps = PreparedComputation(*hit, r);
        Tuple rendered_color = ShadeHit(comps);
        return rendered_color;
    }
    return Tuple::color(0, 0, 0, 1);
}

bool World::IsShadowed(Light &l, Tuple &p) {
    Tuple p_to_light = l.position - p;
    float distance = Tuple::magnitude(p_to_light);
    Tuple direction = Tuple::normalize(p_to_light);
    Ray r(p, direction);
    std::vector<Intersection> xs = IntersectWorld(r);
    std::optional<Intersection> hit = Intersection::Hit(xs);
    if (hit != std::nullopt && hit->t < distance)
        return true;
    return false;
}
