//
// Created by Craig Harris on 9/4/24.
//

#include "HollowGlassSphere.h"

HollowGlassSphere::HollowGlassSphere() {
    outer.material.color = Color::black();
    outer.material.transparency = 1;
    outer.material.refractive_index = 1.5;
    outer.material.reflective = 1;
    outer.material.diffuse = 0.1;
    outer.material.ambient = 0.1;
    outer.material.specular = 1;
    outer.material.shininess = 300;

    inner.material.color = Color::black();
    inner.set_transform(Transformation::scaling(0.99));
    inner.material.transparency = 1;
    inner.material.refractive_index = 1.0;
    inner.material.reflective = 1;
}

void HollowGlassSphere::add_transform(const Matrix &transform) {
    inner.set_transform(transform * inner.get_transform());
    outer.set_transform(transform * outer.get_transform());
}
