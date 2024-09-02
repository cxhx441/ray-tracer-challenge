//
// Created by craig on 8/17/2024.
//

#include "Material.h"

Material::Material(Color color, float ambient, float diffuse, float specular, float shininess, float reflective) :
        color(color),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess),
        reflective(reflective)
        {
    /**
     * ambient, diffuse, specular should be non-negative float between 0 and 1.
     * shininess is best between 10 and 200 but no upper limit is required.
    **/
}

Material::Material(){
    /** default material **/
    color = Color::white();
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
    reflective = 0;
}


void Material::set_pattern(const Pattern& in_pattern) {
    patterns.clear();
    patterns.push_back(in_pattern.clone());
};

void Material::add_pattern(const Pattern& in_pattern) {
    patterns.push_back(in_pattern.clone());
};

bool Material::has_pattern() const {
    return not patterns.empty();
}

Color Material::get_pattern_color(const Tuple &model_point) const {
    Color resulting_color(0, 0, 0, 0);
    for (const auto &pattern: patterns) {
        resulting_color += pattern->color_at(model_point);
    }
    return resulting_color / (float) patterns.size();
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

