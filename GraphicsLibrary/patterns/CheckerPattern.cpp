//
// Created by craig on 8/27/2024.
//

#include "CheckerPattern.h"
#include <cmath>

CheckerPattern::CheckerPattern(Color color_a, Color color_b) : color_a(color_a), color_b(color_b) {}

Color CheckerPattern::pattern_color_at(const Tuple &pattern_point) const {
    float epsilon = 1e-5; // to get rid of "acne".
    int x = floorf(pattern_point.x + epsilon);
    int y = floorf(pattern_point.y + epsilon);
    int z = floorf(pattern_point.z + epsilon);
    if ( (x + y + z) % 2 == 0 )
        return color_a;
    return color_b;
}

