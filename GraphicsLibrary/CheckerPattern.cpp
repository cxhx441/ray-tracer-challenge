//
// Created by craig on 8/27/2024.
//

#include "CheckerPattern.h"
#include <cmath>

CheckerPattern::CheckerPattern(Tuple color_a, Tuple color_b) : color_a(color_a), color_b(color_b) {}

Tuple CheckerPattern::pattern_color_at(const Tuple &pattern_point) const {
    int x = floor(pattern_point.x);
    int y = floor(pattern_point.y);
    int z = floor(pattern_point.z);
    if ( (x + y + z) % 2 == 0 )
        return color_a;
    return color_b;
}

