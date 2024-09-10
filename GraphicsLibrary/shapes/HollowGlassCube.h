//
// Created by craig on 9/5/2024.
//

#ifndef RAYTRACERCHALLENGE_HOLLOWGLASSCUBE_H
#define RAYTRACERCHALLENGE_HOLLOWGLASSCUBE_H

#include "Cube.h"

class HollowGlassCube {
public:
    Cube outer;
    Cube inner;

    HollowGlassCube();
    ~HollowGlassCube() = default;

    void set_color(const Color &color);
    void set_pattern(const Pattern &pattern);
    void casts_shadows(bool cast_shadowb);

    void add_transform(const Matrix &transform);
    void set_transform(const Matrix &transform);
private:
//    float default_inner_scale = 0.999;
    float default_inner_scale = 0.9;
};


#endif //RAYTRACERCHALLENGE_HOLLOWGLASSCUBE_H
