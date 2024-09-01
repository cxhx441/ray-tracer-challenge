//
// Created by Craig Harris on 9/1/24.
//

#ifndef RAYTRACERCHALLENGE_SOLIDPATTERN_H
#define RAYTRACERCHALLENGE_SOLIDPATTERN_H

#include "Pattern.h"

class SolidPattern : public Pattern{
private:
    Tuple color;
public:
    SolidPattern(Tuple color);

    Tuple pattern_color_at(const Tuple &pattern_point) const override;

    std::shared_ptr<Pattern> clone() const override {
        return std::make_shared<SolidPattern>(*this);
    }

    std::vector<Tuple> get_colors(){
        return {color};
    }
};



#endif //RAYTRACERCHALLENGE_SOLIDPATTERN_H
