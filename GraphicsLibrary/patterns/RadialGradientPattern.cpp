//
// Created by craig on 8/31/2024.
//

#include "RadialGradientPattern.h"
#include <cmath>

RadialGradientPattern::RadialGradientPattern(Color color_a, Color color_b) : color_a(color_a), color_b(color_b) {}

Color RadialGradientPattern::pattern_color_at(const Tuple &pattern_point) const {
    float rings = sqrtf( pattern_point.x * pattern_point.x + pattern_point.z * pattern_point.z );
    float fraction = rings - floorf(rings);
    Color color_distance = color_b - color_a; // TODO could save as member.
    return color_a + color_distance * fraction;
}

