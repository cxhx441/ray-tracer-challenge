//
// Created by craig on 8/31/2024.
//

#ifndef RAYTRACERCHALLENGE_RADIALGRADIENTPATTERN_H
#define RAYTRACERCHALLENGE_RADIALGRADIENTPATTERN_H


#include "Pattern.h"
#include "../primitives/Color.h"

class RadialGradientPattern : public Pattern{
public:
    Color color_a = Color::black();
    Color color_b = Color::white();

    RadialGradientPattern() = default;
    RadialGradientPattern(Color color_a, Color color_b);

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<RadialGradientPattern>(*this);
    }
};

#endif //RAYTRACERCHALLENGE_RADIALGRADIENTPATTERN_H
