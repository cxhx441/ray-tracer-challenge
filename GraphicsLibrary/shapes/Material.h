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
    float ambient; // 0 to 1
    float diffuse; // 0 to 1
    float specular; // 0 to 1
    float shininess;  // 0 to 300
    float reflective; // 0 to 1 from non-reflective to mirror
    float transparency; // 0 to 1 from opaque to see-through
    float refractive_index; // 1.0 default makes object so no light bending.

    Material();
    Material(Color color, float ambient, float diffuse, float specular, float shininess, float reflective);

    void set_pattern(const Pattern& in_pattern);

    void add_pattern(const Pattern& in_pattern);

    bool has_pattern() const;

    Color get_pattern_color(const Tuple &model_point) const;

    struct RefractiveIndices{
        static constexpr float glass = 1.5;
    };

    bool operator==(const Material& other) const;
    bool operator!=(const Material& other) const;
};


#endif //RAYTRACERCHAELLENGE_MATERIAL_H
