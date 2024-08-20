#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Transformation.h"
#include "Light.h"
#include "Lighting.h"
#include <filesystem>
#include <cmath>

struct Projectile
{
    Tuple position;
    Tuple velocity;
    Projectile(const Tuple &pos, const Tuple &vel) : position(pos), velocity(vel) {}
};

struct Environment
{
    Tuple gravity;
    Tuple wind;
    Environment(const Tuple &gravity, const Tuple &wind) : gravity(gravity), wind(wind) {}
};

void tick(Projectile* proj, Environment* env) {
    proj->position += proj->velocity;
    proj->velocity += env->gravity + env->wind;
}

void challenge_projectile(){
    Canvas canvas(900, 550);

    Tuple initialPosition = Tuple::vector(0, 1, 0);
    Tuple initialVelocity = Tuple::normalize(Tuple::vector(1, 1.8, 0)) * 11.25;
    Projectile proj(initialPosition, initialVelocity);

    Tuple gravity = Tuple::vector(0, -0.1, 0);
    Tuple wind = Tuple::vector(-0.01, 0, 0);
    Environment env(gravity, wind );


    while (proj.position.y >= 0){
        tick(&proj, &env);
        std::cout << "Projectile Pos: " << proj.position << " Projectile Vel: " << proj.velocity << std::endl;
        try{
            canvas.WritePixel(proj.position.x, canvas.height - proj.position.y, Tuple::color(1, 1, 1, 1));
            canvas.WritePixel(proj.position.x+1, canvas.height - proj.position.y, Tuple::color(1, 1, 1, 1));
            canvas.WritePixel(proj.position.x-1, canvas.height - proj.position.y, Tuple::color(1, 1, 1, 1));
            canvas.WritePixel(proj.position.x, canvas.height - proj.position.y+1, Tuple::color(1, 1, 1, 1));
            canvas.WritePixel(proj.position.x, canvas.height - proj.position.y-1, Tuple::color(1, 1, 1, 1));
        }
        catch(std::invalid_argument const& ex){
            std::cout << ex.what() << std::endl;
        };

    }
    canvas.ToPPMFile("../canvas");

}

void challenge_clock(){
    int size = 1000;
    Canvas canvas(size, size);
    Matrix canvas_transform = Transformation::translation(size/2, size/2, 0);

    int numVertices = 48;
    Tuple p = Tuple::point(0, 0, 0);
    Matrix T = Transformation::translation(1, 0, 0);
    Matrix R = Transformation::rotation_z(2.f * M_PI / numVertices);
    Matrix S = Transformation::scaling(size/2 - size/10);

    p = T * p;

    for (int i = 0; i < numVertices; ++i){
        p = R * p;
        Tuple Sp = S * p;
        std::cout << "Point Pos: " << Sp << std::endl;
        Tuple cp = canvas_transform * Sp;
        try{ canvas.WritePixel(cp.x, cp.y, Tuple::color(1, 1, 1, 1)); }
        catch(std::invalid_argument const& ex){ std::cout << ex.what() << std::endl; };

    }
    canvas.ToPPMFile("../canvas");

}

void challenge_ray_to_sphere(){
    float backdrop_z = 10.f;
    float backdrop_size = 7.f;
    float backdrop_half_size = backdrop_size / 2.f;
    int canvas_size = 256;
    float pixel_size = (float) backdrop_size / (float) canvas_size;
    Tuple color = Tuple::color(1, 0, 0, 1);
    Canvas canvas(canvas_size, canvas_size);

    Sphere s;
    Matrix shear = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix rot = Transformation::rotation_y((355.f/113.f) / 2.f);
    Matrix scale = Transformation::scaling(0.75f);
    s.transform = scale * rot * shear;

    Tuple origin = Tuple::point(0, 0, -5);
    Ray r(origin, Tuple::vector(0, 0, 0));

    for (int y = 0; y < canvas_size; ++y) {
        float world_y = backdrop_half_size - ( pixel_size * y );
        for (int x = 0; x < canvas_size; ++x) {
            float world_x = -backdrop_half_size + ( pixel_size * x );
            Tuple target = Tuple::point(world_x, world_y, backdrop_z);
            r.direction = Tuple::normalize(target - r.origin);
            std::vector<Intersection> xs = Intersection::Intersect(s, r);
            std::optional<Intersection> h = Intersection::Hit(xs);
            if (h) {
                try { canvas.WritePixel(x, y, color); }
                catch (std::invalid_argument const &ex) { std::cout << ex.what() << std::endl; };
            }
        }
    }
    canvas.ToPPMFile("../canvas");
}

void challenge_ray_to_sphere_w_phong_lighting(){
    float backdrop_z = 10.f;
    float backdrop_size = 7.f;
    float backdrop_half_size = backdrop_size / 2.f;
    int canvas_size = 256;
    float pixel_size = (float) backdrop_size / (float) canvas_size;
    Tuple color = Tuple::color(1, 0, 0, 1);
    Canvas canvas(canvas_size, canvas_size);

    Sphere sphere;
    sphere.material = Material();
    sphere.material.color = Tuple::color(1, 0.2, 1, 1);
    Matrix shear = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix rot = Transformation::rotation_y((355.f/113.f) / 2.f);
    Matrix scale = Transformation::scaling(0.75f);
//    sphere.transformation = scale * rot * shear;
//    sphere.transformation = scale * shear;

    Light light = Light::PointLight(Tuple::point(-10, 10, -10), Tuple::color(1, 1, 1, 1));

    Tuple origin = Tuple::point(0, 0, -5);
    Ray ray(origin, Tuple::vector(0, 0, 0));

    for (int y = 0; y < canvas_size; ++y) {
        float world_y = backdrop_half_size - ( pixel_size * y );
        for (int x = 0; x < canvas_size; ++x) {
            float world_x = -backdrop_half_size + ( pixel_size * x );
            Tuple target = Tuple::point(world_x, world_y, backdrop_z);
            ray.direction = Tuple::normalize(target - ray.origin);
            std::vector<Intersection> intersections = Intersection::Intersect(sphere, ray);
            std::optional<Intersection> hit = Intersection::Hit(intersections);
            if (hit) {
                Tuple point = Ray::Position(ray, hit->t);
                Tuple normalv = sphere.NormalAt(point);
                Tuple eyev = -ray.direction;
                color = Lighting::phong_lighting(hit->object->material, light, point, eyev, normalv);
                try { canvas.WritePixel(x, y, color); }
                catch (std::invalid_argument const &ex) { std::cout << ex.what() << std::endl; };
            }
        }
    }
    canvas.ToPPMFile("../canvas");
}

void challenge_world_w_spheres(){
    // Set Spheres
    Sphere floor;
    floor.transform = Transformation::scaling(10, 0.01, 10);
    floor.material.color = Tuple::color(1, 0.9, 0.9, 1);
    floor.material.specular = 0;

    Sphere left_wall;
    left_wall.transform =
            Transformation::translation(1, 0, 5) *
            Transformation::rotation_y(-M_PI_4) *
            Transformation::rotation_x(M_PI_2) *
            Transformation::scaling(10, 0.01, 10);
    left_wall.material = floor.material;

    Sphere right_wall;
    right_wall.transform =
            Transformation::translation(1, 0, 5) *
            Transformation::rotation_y(M_PI_4) *
            Transformation::rotation_x(M_PI_2) *
            Transformation::scaling(10, 0.01, 10);
    right_wall.material = floor.material;

//    Sphere middle;
//    middle.transform = Transformation::translation(-0.5, 1, 0.5);
//    middle.material.color = Tuple::color(0.1, 1, 0.5, 1);
//    middle.material.diffuse = 0.7;
//    middle.material.specular = 0.3;

//    Sphere right;
//    right.transform = Transformation::translation(1.5, 0.5, -0.5) * Transformation::scaling(0.5);
//    right.material.color = Tuple::color(0.5, 1, 0.1, 1);
//    right.material.diffuse = 0.7;
//    right.material.specular = 0.3;
//
//    Sphere left;
//    left.transform = Transformation::translation(-1.5, 0.33, -0.75) * Transformation::scaling(0.33);
//    left.material.color = Tuple::color(1, 0.8, 0.1, 1);
//    left.material.diffuse = 0.7;
//    left.material.specular = 0.3;

    Sphere middle;
    middle.transform = Transformation::translation(-.1, 1.6, -0.3) * Transformation::scaling(0.7);
    middle.material.color = Tuple::color(0.1, 1, 0.5, 1);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right;
    right.transform = Transformation::translation(.5, 0.7, -0.5) * Transformation::scaling(0.7);
    right.material.color = Tuple::color(0.5, 1, 0.1, 1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left;
    left.transform = Transformation::translation(-.5, 0.7, -0.5) * Transformation::scaling(0.7);
    left.material.color = Tuple::color(1, 0.8, 0.1, 1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    Sphere small;
    small.transform = Transformation::translation(-.7, 0.3, -0.8) * Transformation::scaling(0.3);
    small.material.color = Tuple::color(1, 0.2, 0.1, 1);
    small.material.diffuse = 0.7;
    small.material.specular = 0.3;

    Sphere small2;
    small2.transform = Transformation::translation(-.8, 1, -0.7) * Transformation::scaling(0.4);
    small2.material.color = Tuple::color(0.3, 0.2, 1, 1);
    small2.material.diffuse = 0.7;
    small2.material.specular = 0.3;

    // Set Lighting
    Light l1 = Light::PointLight(Tuple::point(-10, 10, -10), Tuple::color(1, 1, 1, 1));

    // Set World
    World world;
//    world.objects.insert(world.objects.end(), {floor, left_wall, right_wall, middle, right, left} );
    world.objects.insert(world.objects.end(), {small, small2, floor, left_wall, right_wall, middle, right, left} );
//    world.objects.insert(world.objects.end(), {small, small2, middle, right, left} );
    world.lights.push_back(l1);

    // Set Camera
    int factor = 2;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.transform = Transformation::view_transform(
            Tuple::point(0, 1.5, -5),
            Tuple::point(0, 1, 0),
            Tuple::vector(0, 1, 0)
    );

    Canvas canvas = Canvas::Render(camera, world);
    std::string filename = "../canvas_";
    filename.append(__FUNCTION__);
    canvas.ToPPMFile(filename);
}

int main()
{
    challenge_world_w_spheres();
    return 0;
}