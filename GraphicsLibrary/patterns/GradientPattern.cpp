//
// Created by craig on 8/27/2024.
//

#include "GradientPattern.h"
#include <cmath>

GradientPattern::GradientPattern(Tuple color_a, Tuple color_b) : color_a(color_a), color_b(color_b) {}

Tuple GradientPattern::pattern_color_at(const Tuple &pattern_point) const {
    float fraction = pattern_point.x - floorf(pattern_point.x);
    Tuple distance = color_b - color_a; // TODO could save as member.
    return color_a + distance * fraction;
}

