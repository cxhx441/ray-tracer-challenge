//
// Created by craig on 8/1/2024.
//

#ifndef RAYTRACERCHAELLENGE_TRANSFORMATION_H
#define RAYTRACERCHAELLENGE_TRANSFORMATION_H

#include "Matrix.h"

class Transformation {
public:
    Matrix translation(float x, float y, float z);
    Matrix scaling(float x, float y, float z);
    Matrix rotation(float x, float y, float z);
};


#endif //RAYTRACERCHAELLENGE_TRANSFORMATION_H
