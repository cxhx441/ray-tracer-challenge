//
// Created by craig on 8/2/2024.
//

#include "Sphere.h"

#include <utility>

Sphere::Sphere(Matrix transformation)
: transformation(std::move(transformation)){}

// Copy constructor
Sphere::Sphere(const Sphere& other)
: material(other.material), transformation(other.transformation) {}

// Move constructor
Sphere::Sphere(Sphere&& other) noexcept
: material(other.material), transformation(std::move(other.transformation)) {}

// Copy assignment operator
Sphere& Sphere::operator=(const Sphere& other) {
    if (this != &other) {
        material = other.material;
        transformation = other.transformation;
    }
    return *this;
}

// Move assignment operator
Sphere& Sphere::operator=(Sphere&& other) noexcept {
    if (this != &other) {
        material = other.material;
        transformation = std::move(other.transformation);
    }
    return *this;
}

// Destructor
Sphere::~Sphere() = default;

Tuple Sphere::NormalAt(Tuple world_point) {
    Tuple model_point = Matrix::Inverse(this->transformation) * world_point;
    Tuple model_normal = model_point - Tuple::point(0, 0, 0);

    Matrix normal_mat = Matrix::NormalMatrix(this->transformation);
    Tuple world_normal = normal_mat * model_normal;
    return Tuple::normalize(world_normal);
}
