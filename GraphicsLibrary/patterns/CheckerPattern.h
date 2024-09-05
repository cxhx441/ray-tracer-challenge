//
// Created by craig on 8/27/2024.
//

#ifndef RAYTRACERCHALLENGE_CHECKERPATTERN_H
#define RAYTRACERCHALLENGE_CHECKERPATTERN_H

#include "Pattern.h"

class CheckerPattern : public Pattern{
public:
    Color color_a = Color::black();
    Color color_b = Color::white();

    CheckerPattern() = default;
    CheckerPattern(Color color_a, Color color_b);

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<CheckerPattern>(*this);
    }
};


#endif //RAYTRACERCHALLENGE_CHECKERPATTERN_H
