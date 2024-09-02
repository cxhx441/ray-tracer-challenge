//
// Created by craig on 8/26/2024.
//

#include "StripedPattern.h"
#include <cmath>

StripedPattern::StripedPattern(Color color_a, Color color_b) : color_a(color_a), color_b(color_b){}

Color StripedPattern::pattern_color_at(const Tuple &pattern_point) const {
    if ( (int)floorf(pattern_point.x) % 2 == 0 )
        return color_a;
    return color_b;
}
