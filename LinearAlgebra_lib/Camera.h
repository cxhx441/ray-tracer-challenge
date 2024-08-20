//
// Created by craig on 8/19/2024.
//

#ifndef RAYTRACERCHAELLENGE_CAMERA_H
#define RAYTRACERCHAELLENGE_CAMERA_H

#include "Matrix.h"
#include "Ray.h"

class Camera {
private:
    Matrix transform = Matrix::Identity(4); // typically like a view_matrix.
    Matrix inverse_transform = Matrix::Inverse(transform); // saving transform for use later.
public:
    int hsize; // width of canvas in pixels
    int vsize; // height of canvas in pixels
    float fov; // angle describing how much the camera can see. Small angle will be zoomed in.
    float half_width;
    float half_height;
    float pixel_size;
    Camera(int hsize, int vsize, float fov);
    void setTransform(Matrix m);
    Matrix getTransform();
    Matrix getInverseTransform();
    static Ray RayForPixel(Camera& c, int x, int y);

};


#endif //RAYTRACERCHAELLENGE_CAMERA_H
