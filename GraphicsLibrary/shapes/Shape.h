//
// Created by craig on 8/21/2024.
//

#ifndef RAYTRACERCHAELLENGE_SHAPE_H
#define RAYTRACERCHAELLENGE_SHAPE_H

#include "../primitives/Transformation.h"
#include "../primitives/Intersection.h"
#include "Material.h"


class Shape {
private:
    Matrix transform = Matrix::identity(4);
    Matrix inverse_transform = Matrix::inverse(transform);
    Matrix normal_transform = Matrix::normal_matrix(transform);

public:
    Material material = Material();

    Shape() = default;

    // virtual destructor
    virtual ~Shape() = default;

    std::string name = "not_given";
    bool casts_shadow = true;

    void set_transform(const Matrix& m);
    Matrix get_transform() const;
    Matrix get_inverse_transform() const;
    Matrix get_normal_transform() const;

//    Sphere(const Sphere& other);                // Copy constructor
//    Sphere(Sphere&& other) noexcept;            // Move constructor
//    Sphere& operator=(const Sphere& other);     // Copy assignment operator
//    Sphere& operator=(Sphere&& other) noexcept; // Move assignment operator

    Color pattern_at(const Tuple& world_point) const;

    virtual std::vector<Intersection> intersect(const Ray& world_ray) const final;
    virtual std::vector<Intersection> model_intersect(const Ray& model_ray) const = 0;
    virtual Tuple normal_at(const Tuple& world_point) const final;
    virtual Tuple model_normal_at(const Tuple& model_point) const = 0; // pure virtual function ie must be overridden in derived class.


};

#endif //RAYTRACERCHAELLENGE_SHAPE_H
