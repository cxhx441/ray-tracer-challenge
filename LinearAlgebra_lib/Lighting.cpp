//
// Created by craig on 8/17/2024.
//

#include "Lighting.h"
#include <cmath>

Tuple Lighting::phong_lighting(const Material &material, const Light &light, const Tuple &point, const Tuple &eyev,
                         const Tuple &normalv) {
    Tuple effective_color = material.color * light.intensity;
    Tuple ambient = Tuple();
    Tuple diffuse = Tuple();
    Tuple specular = Tuple();
//    Tuple diffuse = Tuple();

    Tuple lightv = Tuple::normalize(light.position - point);
    ambient = effective_color * material.ambient;

    float light_dot_normal = Tuple::dot(lightv, normalv);
    if (light_dot_normal < 0){
        diffuse = Tuple::color(0, 0, 0, 1);
        specular = Tuple::color(0, 0, 0, 1);
    }
    else{
        diffuse = effective_color * material.diffuse * light_dot_normal;

        Tuple reflectv = Tuple::reflect(-lightv, normalv);
        float reflect_dot_eye = Tuple::dot(reflectv, eyev);
        if (std::abs(reflect_dot_eye) < 10e-5)
            specular = Tuple::color(0, 0, 0, 1);
        else{
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }
    Tuple lit_color = ambient + diffuse + specular;
    lit_color.w = 1;
    return lit_color;
}
