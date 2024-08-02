//
// Created by craig on 8/1/2024.
//

#ifndef RAYTRACERCHAELLENGE_TRANSFORMATION_H
#define RAYTRACERCHAELLENGE_TRANSFORMATION_H

#include "Matrix.h"

class Transformation {
public:
    static Matrix translation(float x, float y, float z);
    static Matrix scaling(float x, float y, float z);
    static Matrix rotation_x(float radians);
    static Matrix rotation_y(float radians);
    static Matrix rotation_z(float radians);
    static Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);
};


#endif //RAYTRACERCHAELLENGE_TRANSFORMATION_H
