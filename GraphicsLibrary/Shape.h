//
// Created by craig on 8/21/2024.
//

#ifndef RAYTRACERCHAELLENGE_SHAPE_H
#define RAYTRACERCHAELLENGE_SHAPE_H

#include "Transformation.h"
#include "Intersection.h"
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

    // virtual method to clone the shape
//    virtual Shape* clone() const = 0;

    void set_transform(const Matrix& m);
    Matrix get_transform() const;
    Matrix get_inverse_transform() const;
    Matrix get_normal_transform() const;

//    Sphere(const Sphere& other);                // Copy constructor
//    Sphere(Sphere&& other) noexcept;            // Move constructor
//    Sphere& operator=(const Sphere& other);     // Copy assignment operator
//    Sphere& operator=(Sphere&& other) noexcept; // Move assignment operator

    Tuple pattern_at(const Tuple& world_point) const;

    virtual std::vector<Intersection> intersect(const Ray& world_ray) const final;
    virtual std::vector<Intersection> model_intersect(const Ray& model_ray) const = 0;
    virtual Tuple normal_at(const Tuple& world_point) const final;
    virtual Tuple model_normal_at(const Tuple& model_point) const = 0; // pure virtual function ie must be overridden in derived class.


};



class TestShape : public Shape{
public:
    mutable Ray saved_ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 0));

    TestShape() = default;
    ~TestShape() override = default;

    std::vector<Intersection> model_intersect(const Ray &model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
};

#endif //RAYTRACERCHAELLENGE_SHAPE_H
