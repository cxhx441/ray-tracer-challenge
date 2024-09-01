//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_MATERIAL_H
#define RAYTRACERCHAELLENGE_MATERIAL_H

#include "../primitives/Tuple.h"
#include "../patterns/Pattern.h"
#include "../patterns/SolidPattern.h"

class Material {
private:
    std::vector<std::shared_ptr<Pattern>> patterns;
public:
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material();
    Material(float ambient, float diffuse, float specular, float shininess);

    void set_pattern(const Pattern& in_pattern);

    void add_pattern(const Pattern& in_pattern);

    std::shared_ptr<Pattern> get_pattern_at(const size_t idx) const;

    Tuple get_pattern_color(const Tuple &model_point) const;

    bool operator==(const Material& other) const;
    bool operator!=(const Material& other) const;
};


#endif //RAYTRACERCHAELLENGE_MATERIAL_H
