//
// Created by craig on 8/1/2024.
//

#include "Transformation.h"
#include <cmath>

Matrix Transformation::translation(float x, float y, float z){
    Matrix T = Matrix::identity(4);
    T[0][3] = x;
    T[1][3] = y;
    T[2][3] = z;
    return T;
}

Matrix Transformation::scaling(float x, float y, float z){
    Matrix T = Matrix::identity(4);
    T[0][0] = x;
    T[1][1] = y;
    T[2][2] = z;
    return T;
}

Matrix Transformation::scaling(float xyz){
    return scaling(xyz, xyz, xyz);
}

Matrix Transformation::rotation_x(float radians){
    Matrix T = Matrix::identity(4);
    T[1][1] = (float) cos((double) radians);
    T[1][2] = (float) -sin((double) radians);
    T[2][1] = (float) sin((double) radians);
    T[2][2] = (float) cos((double) radians);
    return T;
}

Matrix Transformation::rotation_y(float radians){
    Matrix T = Matrix::identity(4);
    T[0][0] = (float) cos((double) radians);
    T[0][2] = (float) sin((double) radians);
    T[2][0] = (float) -sin((double) radians);
    T[2][2] = (float) cos((double) radians);
    return T;
}

Matrix Transformation::rotation_z(float radians){
    Matrix T = Matrix::identity(4);
    T[0][0] = (float) cos((double) radians);
    T[0][1] = (float) -sin((double) radians);
    T[1][0] = (float) sin((double) radians);
    T[1][1] = (float) cos((double) radians);
    return T;
}

Matrix Transformation::shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
    Matrix T = Matrix::identity(4);
    T[0][1] = xy;
    T[0][2] = xz;
    T[1][0] = yx;
    T[1][2] = yz;
    T[2][0] = zx;
    T[2][1] = zy;
    return T;
}

Ray Transformation::transform(Ray r, const Matrix& m) {
    Tuple o2 = m * r.origin;
    Tuple d2 = m * r.direction;
    return Ray(o2, d2);
}

Matrix Transformation::view_transform(const Tuple &from, const Tuple &to, const Tuple &up) {

    Tuple forward = Tuple::normalized(to - from);
    Tuple left = Tuple::cross(forward, Tuple::normalized(up));
    Tuple true_up = Tuple::cross(left, forward);

    Matrix orientation = Matrix(4, 4);
    orientation.fill({
                             left.x, left.y, left.z, 0,
                             true_up.x, true_up.y, true_up.z, 0,
                             -forward.x, -forward.y, -forward.z, 0,
                             0, 0, 0, 1
                     });

    return orientation * Transformation::translation(-from.x, -from.y, -from.z);
}
