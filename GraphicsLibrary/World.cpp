//
// Created by craig on 8/18/2024.
//

#include "World.h"

World World::DefaultWorld() {
    World w;
    PointLight l(Tuple::point(-10, 10, -10), Tuple::color(1, 1, 1, 1) );
    w.lights.push_back(l);

    // Unit sphere at origin.
    Sphere s1;
    s1.material.color = Tuple::color(0.8, 1.0, 0.6, 1);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    // Half unit sphere at origin.
    Sphere s2;
    s2.set_transform(Transformation::scaling(0.5));

    w.objects.push_back(s1);
    w.objects.push_back(s2);
    return w;
}

std::vector<Intersection> World::intersect_world(Ray &r) {
    std::vector<Intersection> world_xs;
    for (auto& sphere : objects){
        std::vector<Intersection> object_xs = sphere.intersect(r);
        for (auto& x : object_xs){
            world_xs.push_back(x);
        }
    }
    std::sort(world_xs.begin(), world_xs.end());
    return world_xs;
}

Tuple World::shade_hit(PreparedComputation &precompute) {
    Tuple rendered_color(0, 0, 0, 0);
    for (auto light : lights){
        Tuple phong_color = Lighting::phong_lighting(precompute.object->material,
                                                     light,
                                                     precompute.point,
                                                     precompute.eyev,
                                                     precompute.normalv,
                                                     is_shadowed(light, precompute.over_point)
                                                     );
        rendered_color += phong_color;
    }

    // average lights
    rendered_color /= (float) lights.size();

    rendered_color.w = 1;
    return rendered_color;
}

Tuple World::color_at(Ray &r) {
    std::vector<Intersection> xs = intersect_world(r);
    std::optional<Intersection> hit = Intersection::get_hit(xs);
    if (hit != std::nullopt){
        auto comps = PreparedComputation(*hit, r);
        Tuple rendered_color = shade_hit(comps);
        return rendered_color;
    }
    return Tuple::color(0, 0, 0, 1);
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
