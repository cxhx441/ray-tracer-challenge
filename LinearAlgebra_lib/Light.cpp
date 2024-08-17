//
// Created by craig on 8/17/2024.
//

#include "Light.h"

Light Light::PointLight(Tuple position, Tuple intensity) {
    /** intensity is really a color **/
    if (!position.isPoint()){
        throw std::invalid_argument("position must be point");
    }
    return Light(position, intensity);
}

Light::Light(Tuple position, Tuple intensity) : position(position), intensity(intensity){}

