//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_MATERIAL_H
#define RAYTRACERCHAELLENGE_MATERIAL_H

#include "Tuple.h"
#include "Pattern.h"

class Material {
public:
    Tuple color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    Pattern* pattern = nullptr;

    Material();
    Material(Tuple color, float ambient, float diffuse, float specular, float shininess);

    void set_pattern(Pattern* in_pattern) { pattern = in_pattern; }; // TODO set through shape? why pointer?

    bool operator==(const Material& other) const;
    bool operator!=(const Material& other) const;
};


#endif //RAYTRACERCHAELLENGE_MATERIAL_H
