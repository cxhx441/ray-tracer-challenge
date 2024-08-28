//
// Created by craig on 8/27/2024.
//

#include "RingPattern.h"
#include <cmath>

RingPattern::RingPattern(Tuple color_a, Tuple color_b) : color_a(color_a), color_b(color_b) {}

Tuple RingPattern::pattern_color_at(const Tuple &pattern_point) const {
    float intermediate = sqrtf( pattern_point.x * pattern_point.x + pattern_point.z * pattern_point.z );
    if ( (int) floorf( intermediate ) % 2 == 0 )
        return color_a;
    return color_b;
}

