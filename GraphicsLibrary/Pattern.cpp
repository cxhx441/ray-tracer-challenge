//
// Created by craig on 8/26/2024.
//

#include "Pattern.h"

void Pattern::set_transform(const Matrix &m) {
    transform = m;
    inverse_transform = Matrix::inverse(m);
    normal_transform = Matrix::normal_matrix(m);
}

Matrix Pattern::get_transform() const { return transform; }

Matrix Pattern::get_inverse_transform() const { return inverse_transform; }

Matrix Pattern::get_normal_transform() const { return normal_transform; }

Tuple Pattern::color_at(const Tuple &model_point) {
    Tuple pattern_point = get_inverse_transform() * model_point;
    return pattern_color_at(pattern_point);
}


Tuple TestPattern::pattern_color_at(const Tuple &pattern_point) const {
    return {pattern_point.x, pattern_point.y, pattern_point.z, 1};
}
