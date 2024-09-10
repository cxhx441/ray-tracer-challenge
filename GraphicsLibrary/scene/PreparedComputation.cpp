//
// Created by Craig Harris on 8/25/24.
//

#include "PreparedComputation.h"
#include <algorithm>

PreparedComputation::PreparedComputation(Intersection &hit, Ray &r, const std::vector<Intersection> &xs) {

    set_refraction_details( hit, xs );

    t = hit.t;
    object = hit.shape;
    point = Ray::position(r, t);
    eyev = -Tuple::normalized(r.direction);
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
    under_point = point - normalv * REFRACTION_EPSILON;
}


void PreparedComputation::set_refraction_details( Intersection &hit, const std::vector<Intersection> &xs ){
//    std::vector<void*> containers;
    std::vector<std::shared_ptr<const Shape>> containers;

    for ( auto i : xs ){
        // For N1
        if (i == hit) {
            if (containers.empty())
                n1 = 1.0;
            else
                n1 = (containers.back())->material.refractive_index;
        }

        // if object in containers already, the ray is exiting it so remove it, otherwise it's entering it so add it.
        auto found_val = std::find(containers.begin(), containers.end(), i.shape);
        if ( found_val != containers.end()) // found object in containers.
            containers.erase(found_val);
        else
            containers.push_back(i.shape);

        // For N2
        if (i == hit) {
            if (containers.empty())
                n2 = 1.0;
            else
                n2 = (containers.back())->material.refractive_index;
            break;
        }
    }

}