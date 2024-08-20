//
// Created by craig on 8/19/2024.
//

#ifndef RAYTRACERCHAELLENGE_CAMERA_H
#define RAYTRACERCHAELLENGE_CAMERA_H

#include "Matrix.h"
#include "Ray.h"

class Camera {
public:
    int hsize; // width of canvas in pixels
    int vsize; // height of canvas in pixels
    float fov; // angle describing how much the camera can see. Small angle will be zoomed in.
    float half_width;
    float half_height;
    float pixel_size;
    Matrix transform = Matrix::Identity(4); // typically like a view_matrix.
    Camera(int hsize, int vsize, float fov);
    static Ray RayForPixel(Camera& c, int x, int y);

};


#endif //RAYTRACERCHAELLENGE_CAMERA_H
