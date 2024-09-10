//
// Created by craig on 8/18/2024.
//

#ifndef RAYTRACERCHAELLENGE_WORLD_H
#define RAYTRACERCHAELLENGE_WORLD_H

#include "../lights/PointLight.h"
#include "../shapes/Sphere.h"
#include "../shapes/Plane.h"
#include "../shapes/Cube.h"
#include "../shapes/Cylinder.h"
#include "../shapes/Cone.h"
#include "../shapes/HollowGlassSphere.h"
#include "../shapes/HollowGlassCube.h"
#include "../shapes/HollowGlassCylinder.h"
#include "../shapes/HollowGlassCone.h"
#include "PreparedComputation.h"
#include "LightingModels.h"
#include "../primitives/Intersection.h"

class World {
private:
    static bool total_internal_reflection(PreparedComputation &precompute);
public:
    std::vector<PointLight> lights;
    std::vector<std::shared_ptr<Shape>> shapes;

    World() = default;
    static World DefaultWorld();

    void add(PointLight &in_pointlight) ;
    void add(const std::shared_ptr<Shape> &in_shape);
    void add(const std::vector<std::shared_ptr<Shape>> &in_shapes);
    void add(std::vector<PointLight> &in_pointlights) ;


    void add(HollowGlassSphere &hollow_glass_sphere) ;
    void add(HollowGlassCube &hollow_glass_cube) ;
    void add(HollowGlassCylinder &hollow_glass_cylinder) ;
    void add(HollowGlassCone &hollow_glass_cone) ;

    std::vector<Intersection> intersect_world(Ray& r, bool test_for_shadows=false);
    Color shade_hit(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_rays=0);
    Color color_at(Ray& r, bool shadows_enabled=false, int remaining_rays=0);
    bool is_shadowed(PointLight &l, Tuple &p);
    Color reflected_color(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_reflections=0);
    Color refracted_color(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_reflections=0);
    static float schlick_reflectance(PreparedComputation& precompute);

};


#endif //RAYTRACERCHAELLENGE_WORLD_H
