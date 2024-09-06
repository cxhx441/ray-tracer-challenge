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
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Cube> cubes;
    std::vector<Cylinder> cylinders;
    std::vector<Cone> cones;

    World() = default;
    static World DefaultWorld();

    void add(const PointLight &in_pointlight) ;
    void add(const Sphere &in_sphere) ;
    void add(const Plane &in_plane) ;
    void add(const Cube &in_cube) ;
    void add(const Cylinder &in_cylinder) ;
    void add(const Cone &in_cone) ;

    void add(const std::vector<PointLight> &in_pointlights) ;
    void add(const std::vector<Sphere> &in_spheres) ;
    void add(const std::vector<Plane> &in_planes) ;
    void add(const std::vector<Cube> &in_cubes) ;
    void add(const std::vector<Cylinder> &in_cylinders) ;
    void add(const std::vector<Cone> &in_cones) ;

    void add(const HollowGlassSphere &hollow_glass_sphere) ;
    void add(const HollowGlassCube &hollow_glass_cube) ;
    void add(const HollowGlassCylinder &hollow_glass_cylinder) ;
    void add(const HollowGlassCone &hollow_glass_cone) ;
    void add(const std::vector<HollowGlassSphere> &hollow_glass_spheres) ;
    void add(const std::vector<HollowGlassCube> &hollow_glass_cubes) ;
    void add(const std::vector<HollowGlassCylinder> &hollow_glass_cylinders) ;
    void add(const std::vector<HollowGlassCone> &hollow_glass_cones) ;

    std::vector<Intersection> intersect_world(Ray& r, bool test_for_shadows=false);
    Color shade_hit(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_rays=0);
    Color color_at(Ray& r, bool shadows_enabled=false, int remaining_rays=0);
    bool is_shadowed(PointLight &l, Tuple &p);
    Color reflected_color(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_reflections=0);
    Color refracted_color(PreparedComputation& precompute, bool shadows_enabled=false, int remaining_reflections=0);
    static float schlick_reflectance(PreparedComputation& precompute);

};


#endif //RAYTRACERCHAELLENGE_WORLD_H
