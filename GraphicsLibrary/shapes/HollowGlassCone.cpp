//
// Created by Craig Harris on 9/6/24.
//

#include "HollowGlassCone.h"

HollowGlassCone::HollowGlassCone() {
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

void HollowGlassCone::add_transform(const Matrix &transform) {
    inner.set_transform(transform * inner.get_transform());
    outer.set_transform(transform * outer.get_transform());
}

void HollowGlassCone::set_transform(const Matrix &transform) {
    inner.set_transform(transform * Transformation::scaling(default_inner_scale));
    outer.set_transform(transform);
}

void HollowGlassCone::set_color(const Color &color) {
    outer.material.color = color;
}

void HollowGlassCone::set_pattern(const Pattern &pattern) {
    outer.material.set_pattern(pattern);
}

void HollowGlassCone::set_closed(bool closed){
    inner.closed = closed;
    outer.closed = closed;
}
void HollowGlassCone::set_minimum(float minimum){
    inner.minimum = minimum;
    outer.minimum = minimum;
}
void HollowGlassCone::set_maximum(float maximum){
    inner.maximum = maximum;
    outer.maximum = maximum;
}
