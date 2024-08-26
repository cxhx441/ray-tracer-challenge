//
// Created by craig on 8/26/2024.
//

#ifndef RAYTRACERCHALLENGE_STRIPEDPATTERN_H
#define RAYTRACERCHALLENGE_STRIPEDPATTERN_H

#include "Pattern.h"

class StripedPattern : public Pattern{
public:
    Tuple color_a;
    Tuple color_b;

    StripedPattern(Tuple color_a, Tuple color_b);

    Tuple stripe_at(Tuple world_point) const override;
};


#endif //RAYTRACERCHALLENGE_STRIPEDPATTERN_H
