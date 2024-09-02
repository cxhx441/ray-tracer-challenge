//
// Created by craig on 8/27/2024.
//

#ifndef RAYTRACERCHALLENGE_RINGPATTERN_H
#define RAYTRACERCHALLENGE_RINGPATTERN_H

#include "Pattern.h"

class RingPattern : public Pattern{
private:
    Color color_a;
    Color color_b;
public:
    RingPattern(Color color_a, Color color_b);

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<RingPattern>(*this);
    }
};


#endif //RAYTRACERCHALLENGE_RINGPATTERN_H
