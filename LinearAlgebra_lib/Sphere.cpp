//
// Created by craig on 8/2/2024.
//

#include "Sphere.h"

Sphere::Sphere(Matrix transformation) : transformation(transformation){}

Tuple Sphere::NormalAt(Tuple world_point) {
    Tuple model_point = Matrix::Inverse(this->transformation) * world_point;
    Tuple model_normal = model_point - Tuple::point(0, 0, 0);

    Matrix normal_mat = Matrix::NormalMatrix(this->transformation);
    Tuple world_normal = normal_mat * model_normal;
    return Tuple::normalize(world_normal);
}
