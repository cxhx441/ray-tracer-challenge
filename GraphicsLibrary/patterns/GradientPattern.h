//
// Created by craig on 8/27/2024.
//

#ifndef RAYTRACERCHALLENGE_GRADIENTPATTERN_H
#define RAYTRACERCHALLENGE_GRADIENTPATTERN_H

#include "Pattern.h"

class GradientPattern : public Pattern{
private:
    Tuple color_a;
    Tuple color_b;
public:
    GradientPattern(Tuple color_a, Tuple color_b);

    Tuple pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<GradientPattern>(*this);
    }

    std::vector<Tuple> get_colors() const override{
        return {color_a, color_b};
    }
};


#endif //RAYTRACERCHALLENGE_GRADIENTPATTERN_H
