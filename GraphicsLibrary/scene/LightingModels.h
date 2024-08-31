//
// Created by craig on 8/17/2024.
//

#ifndef RAYTRACERCHAELLENGE_LIGHTING_H
#define RAYTRACERCHAELLENGE_LIGHTING_H

#include "../primitives/Tuple.h"
#include "../shapes/Material.h"
#include "../lights/PointLight.h"
#include "../shapes/Shape.h"


class LightingModels {
public:
    static Tuple phong_lighting(const Material &material, const Shape& shape, const PointLight &light, const Tuple &point, const Tuple &eyev, const Tuple &normalv, bool is_shadowed);
};


#endif //RAYTRACERCHAELLENGE_LIGHTING_H
