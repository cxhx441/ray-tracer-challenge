//
// Created by Craig Harris on 9/1/24.
//

#include "TestPattern.h"

Color TestPattern::pattern_color_at(const Tuple &pattern_point) const {
    return {pattern_point.x, pattern_point.y, pattern_point.z, 1};
}
