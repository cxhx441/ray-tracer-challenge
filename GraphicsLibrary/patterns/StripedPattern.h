//
// Created by craig on 8/26/2024.
//

#ifndef RAYTRACERCHALLENGE_STRIPEDPATTERN_H
#define RAYTRACERCHALLENGE_STRIPEDPATTERN_H

#include "Pattern.h"

class StripedPattern : public Pattern{
public:
    Color color_a;
    Color color_b;

    StripedPattern(Color color_a, Color color_b);

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<StripedPattern>(*this);
    }
};


#endif //RAYTRACERCHALLENGE_STRIPEDPATTERN_H
