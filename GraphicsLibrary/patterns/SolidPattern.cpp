//
// Created by Craig Harris on 9/1/24.
//

#include "SolidPattern.h"

SolidPattern::SolidPattern(Tuple color) : color(color){}

Tuple SolidPattern::pattern_color_at(const Tuple &pattern_point) const {
    return color;
}

