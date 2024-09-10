//
// Created by craig on 9/5/2024.
//

#include "HollowGlassCube.h"

HollowGlassCube::HollowGlassCube() {
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
    inner.set_transform(Transformation::scaling(default_inner_scale));
    inner.material.transparency = 1;
    inner.material.refractive_index = 1.0;
    inner.material.reflective = 0;
    inner.material.diffuse = 0;
    inner.material.ambient = 0;
    inner.material.specular = 0;
    inner.material.shininess = 0;
}

void HollowGlassCube::add_transform(const Matrix &transform) {
    inner.set_transform(transform * inner.get_transform());
    outer.set_transform(transform * outer.get_transform());
}

void HollowGlassCube::set_transform(const Matrix &transform) {
    inner.set_transform(transform * Transformation::scaling(default_inner_scale));
    outer.set_transform(transform);
}

void HollowGlassCube::set_color(const Color &color) {
    outer.material.color = color;
}

void HollowGlassCube::set_pattern(const Pattern &pattern) {
    outer.material.set_pattern(pattern);
}

void HollowGlassCube::casts_shadows(bool cast_shadowb) {
    outer.casts_shadow = cast_shadowb;
}
