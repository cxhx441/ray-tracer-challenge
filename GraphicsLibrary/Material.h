//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_MATERIAL_H
#define RAYTRACERCHAELLENGE_MATERIAL_H

#include "Tuple.h"

class Material {
public:
    Tuple color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material();
    Material(Tuple color, float ambient, float diffuse, float specular, float shininess);

    bool operator==(const Material& other) const;
    bool operator!=(const Material& other) const;
};


#endif //RAYTRACERCHAELLENGE_MATERIAL_H
