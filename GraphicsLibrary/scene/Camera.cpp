//
// Created by craig on 8/19/2024.
//

#include "Camera.h"
#include "../primitives/Transformation.h"
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

Ray Camera::ray_for_pixel(Camera &c, int x, int y) {
    /** @brief Generates a worldspace ray through the center of the pixel at the xy coordinate of the canvas **/

    // Offset from edge of canvas to pixel's center
    float xoffset = ( x + 0.5f ) * c.pixel_size;
    float yoffset = ( y + 0.5f) * c.pixel_size;

    // Untransformed coordinates of the pixel in world space.
    // Camera looks toward -z so +x is to the *left*.
    float worldx = c.half_width - xoffset;
    float worldy = c.half_height - yoffset;

    // Using camera matrix, transform canvas point and origin.
    // Then compute the ray's direction vector.
    // REMEMBER canvas is at z = -1 (to make math simpler).
    Tuple pixel = c.get_inverse_transform() * Tuple::point(worldx, worldy, -1);
    Tuple origin = c.get_inverse_transform() * Tuple::point(0, 0, 0);
    Tuple direction = Tuple::normalized(pixel - origin);
    return {origin, direction};
}

void Camera::set_transform(Matrix m) {
    transform = m;
    inverse_transform = Matrix::inverse(m);
}

Matrix Camera::get_transform() {
    return transform;
}

Matrix Camera::get_inverse_transform() {
    return inverse_transform;
}

Camera Camera::unit_sphere_plane_elevation(int h, int v) {
    Camera camera(h, v, M_PI/4.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 0.4, -5),
                    Tuple::point(0, 0.5, 0),
                    Tuple::vector(0, 1, 0)
            )
    );
    return camera;
}

Camera Camera::unit_sphere_plane_angled(int h, int v) {
    Camera camera(h, v, M_PI/4.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 2, -5),
                    Tuple::point(0, 0.5, 0),
                    Tuple::vector(0, 1, 0)
            )
    );
    return camera;
}

Camera Camera::unit_sphere_plane_birds_eye(int h, int v) {
    Camera camera(h, v, M_PI/4.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 3, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );
    return camera;
}
