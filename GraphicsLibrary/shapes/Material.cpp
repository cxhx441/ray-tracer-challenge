//
// Created by craig on 8/17/2024.
//

#include "Material.h"

Material::Material(float ambient, float diffuse, float specular, float shininess) :
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
    set_pattern(SolidPattern(Tuple::color(1, 1, 1, 1)));
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
}


void Material::set_pattern(const Pattern& in_pattern) {
    patterns.clear();
    patterns.push_back(in_pattern.clone());
};

void Material::add_pattern(const Pattern& in_pattern) {
    patterns.push_back(in_pattern.clone());
};

Tuple Material::get_pattern_color(const Tuple &model_point) const {
    Tuple resulting_color(0, 0, 0, 0);
    for (const auto &pattern: patterns) {
        resulting_color += pattern->color_at(model_point);
    }
    return resulting_color / (float) patterns.size();
}

std::shared_ptr<Pattern> Material::get_pattern_at(const size_t idx) const{
    return patterns.at(idx);
}

bool Material::operator==(const Material &other) const {
    if (patterns != other.patterns ||
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

