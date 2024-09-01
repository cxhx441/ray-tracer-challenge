//
// Created by craig on 8/31/2024.
//

#ifndef RAYTRACERCHALLENGE_RADIALGRADIENTPATTERN_H
#define RAYTRACERCHALLENGE_RADIALGRADIENTPATTERN_H


#include "Pattern.h"

class RadialGradientPattern : public Pattern{
private:
    Tuple color_a;
    Tuple color_b;
public:
    RadialGradientPattern(Tuple color_a, Tuple color_b);

    Tuple pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<RadialGradientPattern>(*this);
    }
};

#endif //RAYTRACERCHALLENGE_RADIALGRADIENTPATTERN_H
