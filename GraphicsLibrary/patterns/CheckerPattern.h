//
// Created by craig on 8/27/2024.
//

#ifndef RAYTRACERCHALLENGE_CHECKERPATTERN_H
#define RAYTRACERCHALLENGE_CHECKERPATTERN_H

#include "Pattern.h"

class CheckerPattern : public Pattern{
private:
    Color color_a;
    Color color_b;
public:
    CheckerPattern(Color color_a, Color color_b);

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<CheckerPattern>(*this);
    }
};


#endif //RAYTRACERCHALLENGE_CHECKERPATTERN_H
