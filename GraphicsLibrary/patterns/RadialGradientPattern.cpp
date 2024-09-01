//
// Created by craig on 8/31/2024.
//

#include "RadialGradientPattern.h"
#include <cmath>

RadialGradientPattern::RadialGradientPattern(Tuple color_a, Tuple color_b) : color_a(color_a), color_b(color_b) {}

Tuple RadialGradientPattern::pattern_color_at(const Tuple &pattern_point) const {
    float rings = sqrtf( pattern_point.x * pattern_point.x + pattern_point.z * pattern_point.z );
    float fraction = rings - floorf(rings);
    Tuple distance = color_b - color_a; // TODO could save as member.
    return color_a + distance * fraction;
}

