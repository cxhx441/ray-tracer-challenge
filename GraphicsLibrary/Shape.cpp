//
// Created by craig on 8/21/2024.
//

#include "Shape.h"

void Shape::set_transform(const Matrix &m) {
    transform = m;
    inverse_transform = Matrix::inverse(m);
    normal_transform = Matrix::normal_matrix(m);
}

Matrix Shape::get_transform() const { return transform; }

Matrix Shape::get_inverse_transform() const { return inverse_transform; }

Matrix Shape::get_normal_transform() const { return normal_transform; }

std::vector<Intersection> Shape::intersect(const Ray &world_ray) const {
    Ray model_ray = Transformation::transform( world_ray, this->get_inverse_transform() );
    return model_intersect( model_ray );
}

Tuple Shape::normal_at(const Tuple& world_point) const {
    Tuple model_point = this->get_inverse_transform() * world_point;
    Tuple model_normal = model_normal_at(model_point);
    Tuple world_normal = this->get_normal_transform() * model_normal;
    world_normal.w = 0;
    return Tuple::normalized(world_normal);
}

Tuple Shape::pattern_at(const Tuple &world_point) const {
    Tuple model_point = get_inverse_transform() * world_point;
    return material.pattern->color_at(model_point);
}


Tuple TestShape::model_normal_at(const Tuple& model_point) const {
    return Tuple::vector(model_point.x, model_point.y, model_point.z);
}

std::vector<Intersection> TestShape::model_intersect(const Ray &model_ray) const {
    this->saved_ray = model_ray;
    return {};
}