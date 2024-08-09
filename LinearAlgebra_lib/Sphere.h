//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_SPHERE_H
#define RAYTRACERCHAELLENGE_SPHERE_H

#include "Ray.h"
#include "Transformation.h"
#include <vector>

class Sphere {
public:
    Matrix transformation = Matrix::Identity(4);
    Sphere() = default;
    Tuple NormalAt(Tuple world_point);
    explicit Sphere(Matrix transformation);
};


#endif //RAYTRACERCHAELLENGE_SPHERE_H
