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
    s2.transform = Transformation::scaling(0.5);

    w.objects.push_back(s1);
    w.objects.push_back(s2);
    return w;
}
