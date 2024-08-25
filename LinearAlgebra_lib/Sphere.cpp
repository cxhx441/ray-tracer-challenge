//
// Created by craig on 8/2/2024.
//

#include "Sphere.h"

#include <utility>

// Destructor
Sphere::~Sphere() = default;


//// Copy constructor
//Sphere::Sphere(const Sphere& other)
//: material(other.material), transform(other.transform) {}
//
//// Move constructor
//Sphere::Sphere(Sphere&& other) noexcept
//: material(other.material), transform(std::move(other.transform)) {}
//
//// Copy assignment operator
//Sphere& Sphere::operator=(const Sphere& other) {
//    if (this != &other) {
//        material = other.material;
//        transform = other.transform;
//    }
//    return *this;
//}
//
//// Move assignment operator
//Sphere& Sphere::operator=(Sphere&& other) noexcept {
//    if (this != &other) {
//        material = other.material;
//        transform = std::move(other.transform);
//    }
//    return *this;
//}

Tuple Sphere::NormalAt(Tuple world_point) {
    Tuple model_point = this->getInverseTransform() * world_point;
    Tuple model_normal = model_point - Tuple::point(0, 0, 0);

    Matrix normal_mat = this->getNormalTransform();
    Tuple world_normal = normal_mat * model_normal;
    return Tuple::normalize(world_normal);
}

void Sphere::setTransform(Matrix m) {
    transform = m;
    inverse_transform = Matrix::Inverse(m);
    normal_transform = Matrix::NormalMatrix(m);
}

Matrix Sphere::getTransform() {
    return transform;
}

Matrix Sphere::getInverseTransform() {
    return inverse_transform;
}

Matrix Sphere::getNormalTransform() {
    return normal_transform;
}

std::vector<Intersection> Sphere::Intersect(Ray &r) {
    /**
        Return the times t when the ray intersects the sphere
    **/
    // use the sphere's inverse transformation matrix on the ray first
    Ray trans_ray = Transformation::transform( r, getInverseTransform() );
    Tuple sphere_to_ray = trans_ray.origin - Tuple::point(0, 0,0); // sphere origin is always 000 for simplicity.

    float a = Tuple::dot(trans_ray.direction, trans_ray.direction);
    float b = 2.f * Tuple::dot(trans_ray.direction, sphere_to_ray);
    float c = Tuple::dot(sphere_to_ray, sphere_to_ray) - 1;

    // Check the discriminant is valid
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return std::vector<Intersection>(); // no intersections.

    // If it is, return both t intersections.
    float t1 = (-b - (float) sqrt(discriminant))  / ( 2 * a );
    float t2 = (-b + (float) sqrt(discriminant))  / ( 2 * a );
    return std::vector<Intersection> {Intersection(t1, this), Intersection(t2, this)};
}

