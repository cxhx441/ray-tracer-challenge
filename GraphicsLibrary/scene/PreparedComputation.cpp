//
// Created by Craig Harris on 8/25/24.
//

#include "PreparedComputation.h"

PreparedComputation::PreparedComputation(Intersection &i, Ray &r) {
    t = i.t;
    object = (Sphere *) i.object;
    point = Ray::position(r, t);
    eyev = -r.direction;
    normalv = object->normal_at(point);
    reflectv = Tuple::reflected(r.direction, normalv);
    inside = false;

    // if the eye is inside the object, we still want to color it correctly.
    if ( Tuple::dot(eyev, normalv) < 0 ){
        normalv *= -1;
        inside = true;
    }

    // Adjust the point *slightly* in the direction of the normal. This stops "acne" aka shapes shadowing themselves due to floating point error.
    over_point = point + normalv * SHADOW_EPSILON;
}

