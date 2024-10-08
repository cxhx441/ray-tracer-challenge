//
// Created by Craig Harris on 9/1/24.
//

#ifndef RAYTRACERCHALLENGE_TESTPATTERN_H
#define RAYTRACERCHALLENGE_TESTPATTERN_H

#include "Pattern.h"

class TestPattern : public Pattern{
public:
    TestPattern() = default;

    Color pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<TestPattern>(*this);
    }
};


#endif //RAYTRACERCHALLENGE_TESTPATTERN_H
