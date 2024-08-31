//
// Created by craig on 8/17/2024.
//

#include "Material.h"

Material::Material(Tuple color, float ambient, float diffuse, float specular, float shininess) :
        color(color),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess){
    /**
     * ambient, diffuse, specular should be non-negative float between 0 and 1.
     * shininess is best between 10 and 200 but no upper limit is required.
    **/
}

Material::Material(){
    /** default material **/
    color = Tuple::color(1, 1, 1, 1);
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
}


bool Material::operator==(const Material &other) const {
    if (color != other.color ||
        ambient != other.ambient ||
        diffuse != other.diffuse ||
        specular != other.specular ||
        shininess != other.shininess
    )
        return false;
    return true;
}

bool Material::operator!=(const Material &other) const {
    return !(*this == other);
}

