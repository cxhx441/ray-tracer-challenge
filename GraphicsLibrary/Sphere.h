//
// Created by craig on 8/2/2024.
//

#ifndef RAYTRACERCHAELLENGE_SPHERE_H
#define RAYTRACERCHAELLENGE_SPHERE_H

#include "Ray.h"
#include "Transformation.h"
#include "Material.h"
#include "Intersection.h"
#include <vector>

#include "Shape.h"

class Sphere : public Shape{
public:
    Sphere() = default;
    ~Sphere() override = default;

//    Shape* clone() const override{ return new Sphere(*this); };

    std::vector<Intersection> model_intersect(const Ray& model_ray) const override;
    Tuple model_normal_at(const Tuple& model_point) const override;
};



#endif //RAYTRACERCHAELLENGE_SPHERE_H
