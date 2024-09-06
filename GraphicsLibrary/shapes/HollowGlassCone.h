//
// Created by Craig Harris on 9/6/24.
//

#ifndef RAYTRACERCHALLENGE_HOLLOWGLASSCONE_H
#define RAYTRACERCHALLENGE_HOLLOWGLASSCONE_H

#include "Cone.h"

class HollowGlassCone {
public:
    Cone outer;
    Cone inner;

    HollowGlassCone();
    ~HollowGlassCone() = default;

    void set_color(const Color &color);
    void set_pattern(const Pattern &pattern);
    void set_closed(bool closed);
    void set_minimum(float minimum);
    void set_maximum(float maximum);

    void add_transform(const Matrix &transform);
    void set_transform(const Matrix &transform);
private:
    float default_inner_scale = 0.99;
};

#endif //RAYTRACERCHALLENGE_HOLLOWGLASSCONE_H
