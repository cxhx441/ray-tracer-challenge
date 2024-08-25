//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_SPHERE_H
#define RAYTRACERCHAELLENGE_SPHERE_H

#include "Ray.h"
#include "Transformation.h"
#include "Material.h"
#include "Intersection.h"
#include <vector>

class Sphere {
    Matrix transform = Matrix::identity(4);
    Matrix inverse_transform = Matrix::inverse(transform);
    Matrix normal_transform = Matrix::normal_matrix(transform);
public:
    Material material = Material();

    Sphere() = default;
    ~Sphere();                                  // Destructor

    void set_transform(Matrix m);
    Matrix get_transform();
    Matrix get_inverse_transform();
    Matrix get_normal_transform();

//    Sphere(const Sphere& other);                // Copy constructor
//    Sphere(Sphere&& other) noexcept;            // Move constructor
//    Sphere& operator=(const Sphere& other);     // Copy assignment operator
//    Sphere& operator=(Sphere&& other) noexcept; // Move assignment operator

    Tuple normal_at(Tuple world_point);
    std::vector<Intersection> intersect(Ray& r);
};


#endif //RAYTRACERCHAELLENGE_SPHERE_H
