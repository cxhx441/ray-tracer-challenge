//
// Created by Craig Harris on 9/4/24.
//

#ifndef RAYTRACERCHALLENGE_HOLLOWGLASSSPHERE_H
#define RAYTRACERCHALLENGE_HOLLOWGLASSSPHERE_H

#include "Sphere.h"

class HollowGlassSphere {
public:
    Sphere outer;
    Sphere inner;

    HollowGlassSphere();
    ~HollowGlassSphere() = default;

    void set_color(const Color &color);
    void set_pattern(const Pattern &pattern);

    void add_transform(const Matrix &transform);
    void set_transform(const Matrix &transform);
private:
    float default_inner_scale = 0.99;
};


#endif //RAYTRACERCHALLENGE_HOLLOWGLASSSPHERE_H
