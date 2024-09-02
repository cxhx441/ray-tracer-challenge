//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_MATERIAL_H
#define RAYTRACERCHAELLENGE_MATERIAL_H

#include "../primitives/Tuple.h"
#include "../primitives/Color.h"
#include "../patterns/Pattern.h"

class Material {
private:
    std::vector<std::shared_ptr<Pattern>> patterns;
public:
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflective; // 0 to 1 from non-reflective to mirror

    Material();
    Material(Color color, float ambient, float diffuse, float specular, float shininess, float reflective);

    void set_pattern(const Pattern& in_pattern);

    void add_pattern(const Pattern& in_pattern);

    bool has_pattern() const;

    Color get_pattern_color(const Tuple &model_point) const;

    bool operator==(const Material& other) const;
    bool operator!=(const Material& other) const;
};


#endif //RAYTRACERCHAELLENGE_MATERIAL_H
