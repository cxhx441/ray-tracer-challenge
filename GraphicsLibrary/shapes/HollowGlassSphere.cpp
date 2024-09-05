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
    inner.casts_shadow = false;
    inner.set_transform(Transformation::scaling(0.99));
    inner.material.transparency = 1;
    inner.material.refractive_index = 1.0;
    inner.material.reflective = 0;
    inner.material.diffuse = 0;
    inner.material.ambient = 0;
    inner.material.specular = 0;
    inner.material.shininess = 0;
}

void HollowGlassSphere::add_transform(const Matrix &transform) {
    inner.set_transform(transform * inner.get_transform());
    outer.set_transform(transform * outer.get_transform());
}

void HollowGlassSphere::set_transform(const Matrix &transform) {
    inner.set_transform(transform * Transformation::scaling(0.99));
    outer.set_transform(transform);
}

void HollowGlassSphere::set_color(const Color &color) {
    outer.material.color = color;
}

void HollowGlassSphere::set_pattern(const Pattern &pattern) {
    outer.material.set_pattern(pattern);
}
