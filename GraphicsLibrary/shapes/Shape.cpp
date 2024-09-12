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

Tuple Shape::world_to_object(const Tuple &world_point) const {
    auto point = world_point;

    if ( parent != nullptr ){
        point = parent->world_to_object(point);
    }
    return get_inverse_transform() * point;
}

Tuple Shape::normal_to_world(const Tuple &model_normal) const {
    Tuple normal = get_normal_transform() * model_normal;
    normal.w = 0;
    normal.normalize();

    if ( parent != nullptr ){
        normal = parent->normal_to_world(normal);
    }

    return normal;
}

std::vector<Intersection> Shape::intersect(const Ray &world_ray) const {
    Ray model_ray = Transformation::transform( world_ray, this->get_inverse_transform() );
    return model_intersect( model_ray );
}

Tuple Shape::normal_at(const Tuple& world_point) const {
    Tuple model_point = world_to_object(world_point);
    Tuple model_normal = model_normal_at(model_point);
    return normal_to_world(model_normal);
}

Color Shape::pattern_at(const Tuple &world_point) const {
//    Tuple model_point = get_inverse_transform() * world_point;
    Tuple model_point = world_to_object(world_point);
    return material.get_pattern_color(model_point);
}

