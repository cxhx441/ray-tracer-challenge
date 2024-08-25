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
    Matrix transform = Matrix::Identity(4);
    Matrix inverse_transform = Matrix::Inverse(transform);
    Matrix normal_transform = Matrix::NormalMatrix(transform);
public:
    Material material = Material();

    Sphere() = default;
    ~Sphere();                                  // Destructor

    void setTransform(Matrix m);
    Matrix getTransform();
    Matrix getInverseTransform();
    Matrix getNormalTransform();

//    Sphere(const Sphere& other);                // Copy constructor
//    Sphere(Sphere&& other) noexcept;            // Move constructor
//    Sphere& operator=(const Sphere& other);     // Copy assignment operator
//    Sphere& operator=(Sphere&& other) noexcept; // Move assignment operator

    Tuple NormalAt(Tuple world_point);
    std::vector<Intersection> Intersect(Ray& r);
};


#endif //RAYTRACERCHAELLENGE_SPHERE_H
