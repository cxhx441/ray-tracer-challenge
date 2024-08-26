//
// Created by craig on 8/17/2024.
//

#include "Lighting.h"
#include <cmath>

Tuple Lighting::phong_lighting(const Material &material, const PointLight &light, const Tuple &point, const Tuple &eyev,
                               const Tuple &normalv, bool is_shadowed) {
    Tuple effective_color = material.color * light.color;
    Tuple ambient = Tuple();
    Tuple diffuse = Tuple();
    Tuple specular = Tuple();

    // point to light. Ambient is always added.
    Tuple lightv = Tuple::normalized(light.point - point);
    ambient = effective_color * material.ambient;

    if (is_shadowed){
        ambient.w = 1;
        return ambient;
    }

    // if the angle between light and normal is greater than 90 degrees, no diffuse or specular because light is on other side of surface.
    float light_dot_normal = Tuple::dot(lightv, normalv);
    if (light_dot_normal < 0){
        diffuse = Tuple::color(0, 0, 0, 1);
        specular = Tuple::color(0, 0, 0, 1);
    }
    else{
        diffuse = effective_color * material.diffuse * light_dot_normal;

        Tuple reflectv = Tuple::reflected(-lightv, normalv);

        // if the angle between reflected ray and the eye vector is greater than or equal to 90 degrees, no specular because light is reflected away from the eye.
        float reflect_dot_eye = Tuple::dot(reflectv, eyev);
        if (reflect_dot_eye <= 0)
            specular = Tuple::color(0, 0, 0, 1);
        else{
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.color * material.specular * factor;
        }
    }
    Tuple lit_color = ambient + diffuse + specular;
    lit_color.w = 1;
    return lit_color;
}
