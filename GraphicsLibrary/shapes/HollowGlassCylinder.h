//
// Created by Craig Harris on 9/5/24.
//

#ifndef RAYTRACERCHALLENGE_HOLLOWGLASSCYLINDER_H
#define RAYTRACERCHALLENGE_HOLLOWGLASSCYLINDER_H

#include "Cylinder.h"

class HollowGlassCylinder {
public:
    Cylinder outer;
    Cylinder inner;

    HollowGlassCylinder();
    ~HollowGlassCylinder() = default;

    void set_color(const Color &color);
    void set_pattern(const Pattern &pattern);
    void set_closed(bool closed);
    void set_minimum(float minimum);
    void set_maximum(float maximum);
    void casts_shadows(bool cast_shadowb);

    void add_transform(const Matrix &transform);
    void set_transform(const Matrix &transform);
private:
    float default_inner_scale = 0.99;
};


#endif //RAYTRACERCHALLENGE_HOLLOWGLASSCYLINDER_H
