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

    void add_transform(const Matrix &transform);
};


#endif //RAYTRACERCHALLENGE_HOLLOWGLASSSPHERE_H
