//
// Created by craig on 8/19/2024.
//

#include "Camera.h"
#include <cmath>

Camera::Camera(int hsize, int vsize, float fov) {
    this->hsize = hsize;
    this->vsize = vsize;
    this->fov = fov;

    // The canvas will always be 1 unit away.
    float half_view = tanf(this->fov/2.f);
    float aspect_ratio = (float) this->hsize / (float) this->vsize;
    if ( aspect_ratio >= 1 ){
        this->half_width = half_view;
        this->half_height = half_view / aspect_ratio;
    }
    else{
        this->half_width = half_view * aspect_ratio;
        this->half_height = half_view;
    }

    // Assuming square pixels;
    this->pixel_size = ( this->half_width * 2 )  / (float) this->hsize;
}

Ray Camera::RayForPixel(Camera &c, int x, int y) {
    // Offset from edge of canvas to pixel's center
    float xoffset = ( x + 0.5f ) * c.pixel_size;
    float yoffset = ( y + 0.5f) * c.pixel_size;

    // Untransformed coordinates of the pixel in world space.
    // Camera looks toward -z so +x is to the *left*.
    float worldx = c.half_width - xoffset;
    float worldy = c.half_height - yoffset;

    // Useing camera matrix, transform canvas point and origin.
    // Then compute the ray's direction vector.
    // REMEMBER canvas is at z = -1 (to make math simpler).
    Tuple pixel = Matrix::Inverse(c.transform) * Tuple::point(worldx, worldy, -1);
    Tuple origin = Matrix::Inverse(c.transform) * Tuple::point(0, 0, 0);
    Tuple direction = Tuple::normalize(pixel - origin);
    return Ray(origin, direction);
}
