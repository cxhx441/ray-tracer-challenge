//
// Created by craig on 8/27/2024.
//

#ifndef RAYTRACERCHALLENGE_GRADIENTPATTERN_H
#define RAYTRACERCHALLENGE_GRADIENTPATTERN_H

#include "Pattern.h"

class GradientPattern : public Pattern{
public:
    Color color_a = Color::black();
    Color color_b = Color::white();

    GradientPattern() = default;
    GradientPattern(Color color_a, Color color_b);

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<GradientPattern>(*this);
    }
};


#endif //RAYTRACERCHALLENGE_GRADIENTPATTERN_H
