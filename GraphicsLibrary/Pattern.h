//
// Created by craig on 8/26/2024.
//

#ifndef RAYTRACERCHALLENGE_PATTERN_H
#define RAYTRACERCHALLENGE_PATTERN_H

#include "Tuple.h"
#include "Matrix.h"

class Pattern {
private:
    Matrix transform = Matrix::identity(4);
    Matrix inverse_transform = Matrix::inverse(transform);
    Matrix normal_transform = Matrix::normal_matrix(transform);
public:

    void set_transform(const Matrix& m);
    Matrix get_transform() const;
    Matrix get_inverse_transform() const;
    Matrix get_normal_transform() const;

    virtual Tuple color_at(const Tuple &model_point) final;
    virtual Tuple pattern_color_at(const Tuple &pattern_point) const = 0;
};


class TestPattern : public Pattern{
public:
    TestPattern() = default;

    Tuple pattern_color_at(const Tuple &pattern_point) const override;
};


#endif //RAYTRACERCHALLENGE_PATTERN_H
