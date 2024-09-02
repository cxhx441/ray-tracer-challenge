//
// Created by craig on 8/27/2024.
//

#include "GradientPattern.h"
#include <cmath>

GradientPattern::GradientPattern(Color color_a, Color color_b) : color_a(color_a), color_b(color_b) {}

Color GradientPattern::pattern_color_at(const Tuple &pattern_point) const {
    float fraction = pattern_point.x - floorf(pattern_point.x);
    Color color_distance = color_b - color_a; // TODO could save as member.
    return color_a + color_distance * fraction;
}

