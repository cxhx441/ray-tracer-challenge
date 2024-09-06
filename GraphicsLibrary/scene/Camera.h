//
// Created by craig on 8/19/2024.
//

#ifndef RAYTRACERCHAELLENGE_CAMERA_H
#define RAYTRACERCHAELLENGE_CAMERA_H

#include "../primitives/Matrix.h"
#include "../primitives/Ray.h"

class Camera {
private:
    Matrix transform = Matrix::identity(4); // typically like a view_matrix.
    Matrix inverse_transform = Matrix::inverse(transform); // saving transform for use later.
public:
    int hsize; // width of canvas in pixels
    int vsize; // height of canvas in pixels
    float fov; // angle describing how much the camera can see. Small angle will be zoomed in.
    float half_width;
    float half_height;
    float pixel_size;

    Camera(int hsize, int vsize, float fov);
    static Camera unit_sphere_plane_elevation(int h, int v);
    static Camera unit_sphere_plane_angled(int h, int v);
    static Camera unit_sphere_plane_isometric(int h, int v);
    static Camera unit_sphere_plane_birds_eye(int h, int v);

    void set_transform(Matrix m);
    Matrix get_transform();
    Matrix get_inverse_transform();

    static Ray ray_for_pixel(Camera& c, int x, int y);

};


#endif //RAYTRACERCHAELLENGE_CAMERA_H
