//
// Created by craig on 8/26/2024.
//

#ifndef RAYTRACERCHALLENGE_PATTERN_H
#define RAYTRACERCHALLENGE_PATTERN_H

#include "../primitives/Tuple.h"
#include "../primitives/Matrix.h"
#include "../primitives/Color.h"
#include <memory>

class Pattern {
private:
    Matrix transform = Matrix::identity(4);
    Matrix inverse_transform = Matrix::inverse(transform);
    Matrix normal_transform = Matrix::normal_matrix(transform);
public:
    virtual ~Pattern() = default;
    
    void set_transform(const Matrix& m);
    Matrix get_transform() const;
    Matrix get_inverse_transform() const;
    Matrix get_normal_transform() const;

    virtual Color color_at(const Tuple &model_point) final;
    virtual Color pattern_color_at(const Tuple &pattern_point) const = 0;
    virtual std::shared_ptr<Pattern> clone() const = 0;  // Pure virtual clone method allowing to add different derived patterns to the material class
};


#endif //RAYTRACERCHALLENGE_PATTERN_H
