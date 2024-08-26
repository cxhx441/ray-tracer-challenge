//
// Created by craig on 8/26/2024.
//

#ifndef RAYTRACERCHALLENGE_PATTERN_H
#define RAYTRACERCHALLENGE_PATTERN_H

#include "Tuple.h"

class Pattern {
public:
    virtual Tuple stripe_at(Tuple world_point) const = 0;
};


#endif //RAYTRACERCHALLENGE_PATTERN_H
