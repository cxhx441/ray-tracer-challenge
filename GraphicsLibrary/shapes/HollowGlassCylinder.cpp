//
// Created by Craig Harris on 9/5/24.
//

#include "HollowGlassCylinder.h"

HollowGlassCylinder::HollowGlassCylinder() {
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

void HollowGlassCylinder::add_transform(const Matrix &transform) {
    inner.set_transform(transform * inner.get_transform());
    outer.set_transform(transform * outer.get_transform());
}

void HollowGlassCylinder::set_transform(const Matrix &transform) {
    inner.set_transform(transform * Transformation::scaling(default_inner_scale));
    outer.set_transform(transform);
}

void HollowGlassCylinder::set_color(const Color &color) {
    outer.material.color = color;
}

void HollowGlassCylinder::set_pattern(const Pattern &pattern) {
    outer.material.set_pattern(pattern);
}

void HollowGlassCylinder::set_closed(bool closed){
    inner.closed = closed;
    outer.closed = closed;
}
void HollowGlassCylinder::set_minimum(float minimum){
    inner.minimum = minimum + ( 1 - default_inner_scale );
    outer.minimum = minimum;
}
void HollowGlassCylinder::set_maximum(float maximum){
    inner.maximum = maximum - ( 1 - default_inner_scale );
    outer.maximum = maximum;
}

void HollowGlassCylinder::casts_shadows(bool cast_shadowb) {
    outer.casts_shadow = cast_shadowb;
}
