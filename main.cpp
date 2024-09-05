#include <iostream>
#include "GraphicsLibrary/display/Canvas.h"
#include "GraphicsLibrary/shapes/Sphere.h"
#include "GraphicsLibrary/shapes/Plane.h"
#include "GraphicsLibrary/patterns/StripedPattern.h"
#include "GraphicsLibrary/patterns/RingPattern.h"
#include "GraphicsLibrary/patterns/GradientPattern.h"
#include "GraphicsLibrary/patterns/CheckerPattern.h"
#include "GraphicsLibrary/patterns/RadialGradientPattern.h"
#include <cmath>
#include <chrono>

void render_time_and_save(Camera &camera, World &world, bool shadows_enabled, int num_reflections, std::string function_name){
    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world, shadows_enabled, num_reflections);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(function_name + "_" + std::to_string(shadows_enabled) + "shad_" + std::to_string(num_reflections) + "ref");
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

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
    Tuple initialVelocity = Tuple::normalized(Tuple::vector(1, 1.8, 0)) * 11.25;
    Projectile proj(initialPosition, initialVelocity);

    Tuple gravity = Tuple::vector(0, -0.1, 0);
    Tuple wind = Tuple::vector(-0.01, 0, 0);
    Environment env(gravity, wind );


    while (proj.position.y >= 0){
        tick(&proj, &env);
        std::cout << "Projectile Pos: " << proj.position << " Projectile Vel: " << proj.velocity << std::endl;
        try{
            canvas.write_pixel(proj.position.x, canvas.height - proj.position.y, Color::white());
            canvas.write_pixel(proj.position.x + 1, canvas.height - proj.position.y, Color::white());
            canvas.write_pixel(proj.position.x - 1, canvas.height - proj.position.y, Color::white());
            canvas.write_pixel(proj.position.x, canvas.height - proj.position.y + 1, Color::white());
            canvas.write_pixel(proj.position.x, canvas.height - proj.position.y - 1, Color::white());
        }
        catch(std::invalid_argument const& ex){
            std::cout << ex.what() << std::endl;
        };

    }
    canvas.to_ppm_file("../canvas");

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
        try{ canvas.write_pixel(cp.x, cp.y, Color::white()); }
        catch(std::invalid_argument const& ex){ std::cout << ex.what() << std::endl; };

    }
    canvas.to_ppm_file("../canvas");

}

void challenge_ray_to_sphere(){
    float backdrop_z = 10.f;
    float backdrop_size = 7.f;
    float backdrop_half_size = backdrop_size / 2.f;
    int canvas_size = 256;
    float pixel_size = (float) backdrop_size / (float) canvas_size;
    Color color = Color::red();
    Canvas canvas(canvas_size, canvas_size);

    Sphere s;
    Matrix shear = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix rot = Transformation::rotation_y((355.f/113.f) / 2.f);
    Matrix scale = Transformation::scaling(0.75f);
    s.set_transform(scale * rot * shear);

    Tuple origin = Tuple::point(0, 0, -5);
    Ray r(origin, Tuple::vector(0, 0, 0));

    for (int y = 0; y < canvas_size; ++y) {
        float world_y = backdrop_half_size - ( pixel_size * y );
        for (int x = 0; x < canvas_size; ++x) {
            float world_x = -backdrop_half_size + ( pixel_size * x );
            Tuple target = Tuple::point(world_x, world_y, backdrop_z);
            r.direction = Tuple::normalized(target - r.origin);
            std::vector<Intersection> xs = s.intersect(r);
            std::optional<Intersection> h = Intersection::get_hit(xs);
            if (h) {
                try { canvas.write_pixel(x, y, color); }
                catch (std::invalid_argument const &ex) { std::cout << ex.what() << std::endl; };
            }
        }
    }
    canvas.to_ppm_file("../canvas");
}

void challenge_ray_to_sphere_w_phong_lighting(){
    float backdrop_z = 10.f;
    float backdrop_size = 7.f;
    float backdrop_half_size = backdrop_size / 2.f;
    int canvas_size = 256;
    float pixel_size = (float) backdrop_size / (float) canvas_size;
    Color color = Color::red();
    Canvas canvas(canvas_size, canvas_size);

    Sphere sphere;
    sphere.material = Material();
    sphere.material.color = Color(1, 0.2, 1, 1);
    Matrix shear = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix rot = Transformation::rotation_y((355.f/113.f) / 2.f);
    Matrix scale = Transformation::scaling(0.75f);
//    sphere.transformation = scale * rot * shear;
//    sphere.transformation = scale * shear;

    PointLight light(Tuple::point(-10, 10, -10), Color::white());

    Tuple origin = Tuple::point(0, 0, -5);
    Ray ray(origin, Tuple::vector(0, 0, 0));

    for (int y = 0; y < canvas_size; ++y) {
        float world_y = backdrop_half_size - ( pixel_size * y );
        for (int x = 0; x < canvas_size; ++x) {
            float world_x = -backdrop_half_size + ( pixel_size * x );
            Tuple target = Tuple::point(world_x, world_y, backdrop_z);
            ray.direction = Tuple::normalized(target - ray.origin);
            std::vector<Intersection> intersections = sphere.intersect(ray);
            std::optional<Intersection> hit = Intersection::get_hit(intersections);
            if (hit) {
                Tuple point = Ray::position(ray, hit->t);
                Tuple normalv = sphere.normal_at(point);
                Tuple eyev = -ray.direction;
//                color = Lighting::phong_lighting(((Sphere *) hit->object)->material, light, point, eyev, normalv, false);
                auto *s = (Sphere*) hit->object;
                color = LightingModels::phong_lighting(s->material, *s, light, point, eyev, normalv, false);
                try { canvas.write_pixel(x, y, color); }
                catch (std::invalid_argument const &ex) { std::cout << ex.what() << std::endl; };
            }
        }
    }
    canvas.to_ppm_file("../canvas");
}

void challenge_world_w_spheres(){
    // Set Spheres
    Sphere floor;
    floor.set_transform(Transformation::scaling(10, 0.01, 10));
    floor.material.color = Color(1, 0.9, 0.9, 1);
    floor.material.specular = 0;

    Sphere left_wall;
    left_wall.set_transform(
            Transformation::translation(1, 0, 5) *
            Transformation::rotation_y(-M_PI_4) *
            Transformation::rotation_x(M_PI_2) *
            Transformation::scaling(10, 0.01, 10)
    );
    left_wall.material = floor.material;

    Sphere right_wall;
    right_wall.set_transform(
            Transformation::translation(1, 0, 5) *
            Transformation::rotation_y(M_PI_4) *
            Transformation::rotation_x(M_PI_2) *
            Transformation::scaling(10, 0.01, 10)
    );
    right_wall.material = floor.material;

    Sphere middle;
    middle.set_transform(Transformation::translation(-.1, 1.6, -0.3) * Transformation::scaling(0.7));
    middle.material.color = Color(0.1, 1, 0.5, 1);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right;
    right.set_transform(Transformation::translation(.5, 0.7, -0.5) * Transformation::scaling(0.7));
    right.material.color = Color(0.5, 1, 0.1, 1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left;
    left.set_transform(Transformation::translation(-.5, 0.7, -0.5) * Transformation::scaling(0.7));
    left.material.color = Color(1, 0.8, 0.1, 1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.8;

    Sphere small;
    small.set_transform(Transformation::translation(-.7, 0.3, -0.8) * Transformation::scaling(0.3));
    small.material.color = Color(1, 0.2, 0.1, 1);
    small.material.diffuse = 0.7;
    small.material.specular = 0.8;

    Sphere small2;
    small2.set_transform(
            Transformation::translation(-.8, 1, -0.7) *
            Transformation::scaling(0.4) *
            Transformation::shearing(2, 0, 0, 0 ,0, 0)
            );
    small2.material.color = Color(0.3, 0.2, 1, 1);
    small2.material.diffuse = 0.7;
    small2.material.specular = 0.8;
    small2.material.shininess = 200;

    // Set Lighting
    PointLight l1(Tuple::point(-10, 10, -10), Color::white());
    PointLight l2(Tuple::point(-10, 0, -10), Color::white());
    PointLight l3(Tuple::point(0, 10, -10), Color::white());
    PointLight l4(Tuple::point(10, 0, -10), Color::white());

    // Set World
    World world;
//    world.spheres.insert(world.spheres.end(), {floor, left_wall, right_wall, middle, right, left} );
    world.spheres.insert(world.spheres.end(), {small, small2, floor, left_wall, right_wall, middle, right, left} );
//    world.spheres.insert(world.spheres.end(), {small, small2, middle, right, left} );
//    world.spheres.insert(world.spheres.end(), {small});
    world.lights.push_back(l1);
//    world.lights.push_back(l2);
//    world.lights.push_back(l3);
//    world.lights.push_back(l4);

    // Set Camera
    int factor = 1;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 1.5, -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void custom_scene(){
    Sphere floor;
    floor.set_transform(Transformation::scaling(10, 0.01, 10));
    floor.material.color = Color(1, 0.9, 0.9, 1);
    floor.material.specular = 0;

    Sphere left_wall;
    left_wall.set_transform(
            Transformation::translation(1, 0, 5) *
            Transformation::rotation_y(-M_PI_4) *
            Transformation::rotation_x(M_PI_2) *
            Transformation::scaling(10, 0.01, 10)
    );
    left_wall.material = floor.material;

    Sphere right_wall;
    right_wall.set_transform(
            Transformation::translation(1, 0, 5) *
            Transformation::rotation_y(M_PI_4) *
            Transformation::rotation_x(M_PI_2) *
            Transformation::scaling(10, 0.01, 10)
    );
    right_wall.material = floor.material;

    Sphere redDome;
    redDome.set_transform(Transformation::translation(-1.5, .8, 1) * Transformation::scaling(0.35));
    redDome.material.color = Color(1, 0.2, 0.1, 1);
    redDome.material.diffuse = 0.7;
    redDome.material.specular = 0.8;

    Sphere blueDisk;
    blueDisk.set_transform(
            Transformation::translation(-1.5, .8, 1) *
            Transformation::rotation_x(-M_PI_4) *
            Transformation::rotation_z(-M_PI / 5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    blueDisk.material.color = Color(0.3, 0.2, 1, 1);
    blueDisk.material.diffuse = 0.7;
    blueDisk.material.specular = 0.8;
    blueDisk.material.shininess = 200;

    Sphere blueDome;
    blueDome.set_transform(Transformation::translation(1.5, 1.5, 1.3) * Transformation::scaling(0.35));
    blueDome.material.color = Color(0.3, 0.2, 1, 1);
    blueDome.material.diffuse = 0.7;
    blueDome.material.specular = 0.8;

    Sphere redDisk;
    redDisk.set_transform(
            Transformation::translation(1.5, 1.5, 1.3) *
            Transformation::rotation_y(-M_PI / 3) *
            Transformation::rotation_z(M_PI / 2.5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    redDisk.material.color = Color(1, 0.2, 0.1, 1);
    redDisk.material.diffuse = 0.7;
    redDisk.material.specular = 0.8;
    redDisk.material.shininess = 200;

    Sphere origin;
    origin.set_transform(Transformation::scaling(0.05));

    // Set Lighting
    PointLight l1(Tuple::point(-10, 10, -10), Color::magenta());
    PointLight l2(Tuple::point(-5, 10, -10), Color::white());
    PointLight l3(Tuple::point(-0, 10, -10), Color::white());
    PointLight l4(Tuple::point(5, 10, -10), Color::white());
    PointLight l5(Tuple::point(0, 10, 0), Color::white());
    PointLight l6(Tuple::point(0, 10, -1), Color::white());

    // Set World
    World world;
//        world.spheres.insert(world.spheres.end(), {small, small2} );
//        world.spheres.insert(world.spheres.end(), {skysphere, small, small2} );
//    world.spheres.insert(world.spheres.end(), {floor, ceiling, back_wall, left_wall, right_wall, small, small2} );
    world.spheres.insert(world.spheres.end(), {origin, floor, left_wall, right_wall, redDome, blueDisk, blueDome, redDisk} );
//        world.spheres.insert(world.spheres.end(), {skysphere} );
    world.lights.push_back(l1);
//    world.lights.push_back(l2);
//    world.lights.push_back(l3);
//    world.lights.push_back(l4);
//    world.lights.push_back(l5);
//    world.lights.push_back(l6);

    // Set Camera
    int factor = 1;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 1.5, -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);

};

void challenge_plane(){
    Plane floor;
    Plane back_wall;
    back_wall.set_transform(Transformation::translation(0, 0, 3) * Transformation::rotation_x(M_PI_2));

    Sphere redDome;
    redDome.set_transform(Transformation::translation(-1.5, .8, 1) * Transformation::scaling(0.35));
    redDome.material.color = Color(1, 0.2, 0.1, 1);
    redDome.material.diffuse = 0.7;
    redDome.material.specular = 0.8;

    Sphere blueDisk;
    blueDisk.set_transform(
            Transformation::translation(-1.5, .8, 1) *
            Transformation::rotation_x(-M_PI_4) *
            Transformation::rotation_z(-M_PI / 5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    blueDisk.material.color = Color(0.3, 0.2, 1, 1);
    blueDisk.material.diffuse = 0.7;
    blueDisk.material.specular = 0.8;
    blueDisk.material.shininess = 200;

    Sphere blueDome;
    blueDome.set_transform(Transformation::translation(1.5, 1.5, 1.3) * Transformation::scaling(0.35));
    blueDome.material.color = Color(0.3, 0.2, 1, 1);
    blueDome.material.diffuse = 0.7;
    blueDome.material.specular = 0.8;

    Sphere redDisk;
    redDisk.set_transform(
            Transformation::translation(1.5, 1.5, 1.3) *
            Transformation::rotation_y(-M_PI / 3) *
            Transformation::rotation_z(M_PI / 2.5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    redDisk.material.color = Color(1, 0.2, 0.1, 1);
    redDisk.material.diffuse = 0.7;
    redDisk.material.specular = 0.8;
    redDisk.material.shininess = 200;

    Sphere origin;
    origin.set_transform(Transformation::scaling(0.05));

    // Set Lighting
    PointLight l1(Tuple::point(-10, 10, -10), Color::white());
    PointLight l2(Tuple::point(-5, 10, -10), Color::white());
    PointLight l3(Tuple::point(-0, 10, -10), Color::white());
    PointLight l4(Tuple::point(5, 10, -10), Color::white());
    PointLight l5(Tuple::point(0, 10, 0), Color::white());
    PointLight l6(Tuple::point(0, 10, -1), Color::white());

    // Set World
    World world;

    world.spheres.insert(world.spheres.end(), {origin, redDome, blueDisk, blueDome, redDisk} );

    world.planes.insert(world.planes.end(), {floor, back_wall});

    world.lights.push_back(l1);
//    world.lights.push_back(l2);
//    world.lights.push_back(l3);
//    world.lights.push_back(l4);
//    world.lights.push_back(l5);
//    world.lights.push_back(l6);

    // Set Camera
    int factor = 2;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 1.5, -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);


}

void non_transformed_patterns(){
    Plane floor;
    Plane back_wall;
    back_wall.set_transform(Transformation::translation(0, 0, 3) * Transformation::rotation_x(M_PI_2));

    Sphere redDome;
    redDome.set_transform(Transformation::translation(-1.5, .8, 1) * Transformation::scaling(0.35));
    redDome.material.color = Color(1, 0.2, 0.1, 1);
    redDome.material.diffuse = 0.7;
    redDome.material.specular = 0.8;

    Sphere blueDisk;
    blueDisk.set_transform(
            Transformation::translation(-1.5, .8, 1) *
            Transformation::rotation_x(-M_PI_4) *
            Transformation::rotation_z(-M_PI / 5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    blueDisk.material.color = Color(0.3, 0.2, 1, 1);
    blueDisk.material.diffuse = 0.7;
    blueDisk.material.specular = 0.8;
    blueDisk.material.shininess = 200;

    Sphere blueDome;
    blueDome.set_transform(Transformation::translation(1.5, 1.5, 1.3) * Transformation::scaling(0.35));
    blueDome.material.color = Color(0.3, 0.2, 1, 1);
    blueDome.material.diffuse = 0.7;
    blueDome.material.specular = 0.8;

    Sphere redDisk;
    redDisk.set_transform(
            Transformation::translation(1.5, 1.5, 1.3) *
            Transformation::rotation_y(-M_PI / 3) *
            Transformation::rotation_z(M_PI / 2.5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    redDisk.material.color = Color(1, 0.2, 0.1, 1);
    redDisk.material.diffuse = 0.7;
    redDisk.material.specular = 0.8;
    redDisk.material.shininess = 200;

    //set patterns
    StripedPattern p1(Color::cyan(), Color::magenta());
    redDisk.material.set_pattern(p1);
    blueDisk.material.set_pattern(p1);

    StripedPattern p2(Color::white(), Color::cyan());
    floor.material.set_pattern(p2);

    StripedPattern p3(Color::cyan(), Color::white());
    back_wall.material.set_pattern(p3);

    Sphere origin;
    origin.set_transform(Transformation::scaling(0.05));

    // Set Lighting
    PointLight l1(Tuple::point(-10, 10, -10), Color::white());
    PointLight l2(Tuple::point(-5, 10, -10), Color::white());
    PointLight l3(Tuple::point(-0, 10, -10), Color::white());
    PointLight l4(Tuple::point(5, 10, -10), Color::white());
    PointLight l5(Tuple::point(0, 10, 0), Color::white());
    PointLight l6(Tuple::point(0, 10, -1), Color::white());

    // Set World
    World world;

    world.spheres.insert(world.spheres.end(), {origin, redDome, blueDisk, blueDome, redDisk} );
    world.spheres.insert(world.spheres.end(), {origin, redDome, blueDisk, blueDome, redDisk} );

    world.planes.insert(world.planes.end(), {floor, back_wall});

    world.lights.push_back(l1);
//    world.lights.push_back(l2);
//    world.lights.push_back(l3);
//    world.lights.push_back(l4);
//    world.lights.push_back(l5);
//    world.lights.push_back(l6);

    // Set Camera
    int factor = 8;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 1.5, -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void transformed_patterns(){
    Plane floor;
    Plane back_wall;
    back_wall.set_transform(Transformation::translation(0, 0, 3) * Transformation::rotation_x(M_PI_2));

    Sphere redDome;
    redDome.set_transform(Transformation::translation(-1.5, .8, 1) * Transformation::scaling(0.35));
    redDome.material.color = Color(1, 0.2, 0.1, 1);
    redDome.material.diffuse = 0.7;
    redDome.material.specular = 0.8;

    Sphere blueDisk;
    blueDisk.set_transform(
            Transformation::translation(-1.5, .8, 1) *
            Transformation::rotation_x(-M_PI_4) *
            Transformation::rotation_z(-M_PI / 5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    blueDisk.material.color = Color(0.3, 0.2, 1, 1);
    blueDisk.material.diffuse = 0.7;
    blueDisk.material.specular = 0.8;
    blueDisk.material.shininess = 200;

    Sphere blueDome;
    blueDome.set_transform(Transformation::translation(1.5, 1.5, 1.3) * Transformation::scaling(0.35));
    blueDome.material.color = Color(0.3, 0.2, 1, 1);
    blueDome.material.diffuse = 0.7;
    blueDome.material.specular = 0.8;

    Sphere redDisk;
    redDisk.set_transform(
            Transformation::translation(1.5, 1.5, 1.3) *
            Transformation::rotation_y(-M_PI / 3) *
            Transformation::rotation_z(M_PI / 2.5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    redDisk.material.color = Color(1, 0.2, 0.1, 1);
    redDisk.material.diffuse = 0.7;
    redDisk.material.specular = 0.8;
    redDisk.material.shininess = 200;

    //set patterns
    StripedPattern p1(Color::magenta(), Color::green());
    p1.set_transform(Transformation::scaling(0.01));
    redDisk.material.set_pattern(p1);
    blueDisk.material.set_pattern(p1);

    StripedPattern p2(Color::white(), Color::cyan());
    floor.material.set_pattern(p2);

    StripedPattern p3(Color::cyan(), Color::white());
    p3.set_transform(Transformation::scaling(0.1));
    back_wall.material.set_pattern(p3);

    Sphere origin;
    origin.set_transform(Transformation::scaling(0.05));

    // Set Lighting
    PointLight l1(Tuple::point(-10, 10, -10), Color::white());
    PointLight l2(Tuple::point(-5, 10, -10), Color::white());
    PointLight l3(Tuple::point(-0, 10, -10), Color::white());
    PointLight l4(Tuple::point(5, 10, -10), Color::white());
    PointLight l5(Tuple::point(0, 10, 0), Color::white());
    PointLight l6(Tuple::point(0, 10, -1), Color::white());

    // Set World
    World world;

    world.spheres.insert(world.spheres.end(), {origin, redDome, blueDisk, blueDome, redDisk} );

    world.planes.insert(world.planes.end(), {floor, back_wall});

    world.lights.push_back(l1);
//    world.lights.push_back(l2);
//    world.lights.push_back(l3);
//    world.lights.push_back(l4);
//    world.lights.push_back(l5);
//    world.lights.push_back(l6);

    // Set Camera
    int factor = 160;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 1.5, -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_sphere_patterns_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    StripedPattern stripes(orange, blue);
    GradientPattern gradient(orange, blue);
    RingPattern rings(orange, blue);
    CheckerPattern checkers(orange, blue);

    stripes.set_transform(Transformation::scaling(0.1));
    gradient.set_transform(Transformation::scaling(2, 1, 1) * Transformation::translation(0.5, 0, 0));
    rings.set_transform(Transformation::scaling(0.085));
    checkers.set_transform(Transformation::scaling(0.25));

    // Shapes
    Sphere striped_sphere;
    Sphere gradient_sphere;
    Sphere ring_sphere;
    Sphere checkered_sphere;

    Plane regular_plane;
    Plane striped_plane;
    Plane gradient_plane;
    Plane ring_plane;
    Plane checkered_plane;

//    striped_sphere.set_transform(Transformation::translation(-2.25, 0, 1) * Transformation::scaling(.6));
//    gradient_sphere.set_transform(Transformation::translation(-0.75, 0, 1) * Transformation::scaling(.6));
//    ring_sphere.set_transform(Transformation::translation(.75, 0, 1) * Transformation::scaling(.6));
//    checkered_sphere.set_transform(Transformation::translation(2.25, 0, 1) * Transformation::scaling(.6));
    float sphere_size = .9;
    float delta = 2.2;
    float two = -delta / 2;
    float three = delta / 2;
    float one = two - delta;
    float four = three + delta;

    float y_up = 0;
    striped_sphere.set_transform(Transformation::translation(one, y_up, 1) * Transformation::scaling(sphere_size));
    gradient_sphere.set_transform(Transformation::translation(two, y_up, 1) * Transformation::scaling(sphere_size));
    ring_sphere.set_transform(Transformation::translation(three, y_up, 1) * Transformation::scaling(sphere_size));
    checkered_sphere.set_transform(Transformation::translation(four, y_up, 1) * Transformation::scaling(sphere_size));

    striped_sphere.material.set_pattern(stripes);
    gradient_sphere.material.set_pattern(gradient);
    ring_sphere.material.set_pattern(rings);
    checkered_sphere.material.set_pattern(checkers);

    regular_plane.set_transform(Transformation::translation(0, -1, 0));
//    striped_plane;
//    gradient_plane;
//    ring_plane;
//    checkered_plane;

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.insert(world.spheres.end(), {striped_sphere, gradient_sphere, ring_sphere, checkered_sphere} );
    world.planes.push_back(regular_plane);
//    world.planes.insert(world.planes.end(), {striped_plane, gradient_plane, ring_plane, checkered_plane} );
    world.lights.push_back(light);

    int factor = 40;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
            Tuple::point(0, 4., -5),
            Tuple::point(0, 1, 0),
            Tuple::vector(0, 1, 0)
    )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_stripe_patterns_plane_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    StripedPattern stripes(orange, blue);
    Plane striped_plane;
    striped_plane.material.set_pattern(stripes);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.planes.insert(world.planes.end(), {striped_plane} );
    world.lights.push_back(light);

    int factor = 20;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10, -10),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_gradient_patterns_plane_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    GradientPattern gradient(orange, blue);
    Plane gradient_plane;
    gradient_plane.material.set_pattern(gradient);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.planes.insert(world.planes.end(), {gradient_plane} );
    world.lights.push_back(light);

    int factor = 20;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10, -10),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 1, 0)
            )
    );


    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_ring_patterns_plane_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    RingPattern rings(orange, blue);
    Plane ring_plane;
    ring_plane.material.set_pattern(rings);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.planes.insert(world.planes.end(), {ring_plane} );
    world.lights.push_back(light);

    int factor = 20;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10, -10),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 1, 0)
            )
    );


    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_checker_pattern_plane_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    CheckerPattern checkers(orange, blue);
    Plane checkered_plane;
    checkered_plane.material.set_pattern(checkers);

    // light
    PointLight light(Tuple::point(0, 10, 0), Color::white());

    // world
    World world;
    world.planes.insert(world.planes.end(), {checkered_plane} );
    world.lights.push_back(light);

    int factor = 20;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10, -10),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_radialgrad_pattern_plane_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    RadialGradientPattern radialgrad(orange, blue);
    Plane radgrad_plane;
    radgrad_plane.material.set_pattern(radialgrad);

    // light
    PointLight light(Tuple::point(0, 10, 0), Color::white());

    // world
    World world;
    world.planes.insert(world.planes.end(), {radgrad_plane} );
    world.lights.push_back(light);

    int factor = 8;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10, -10),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}
void basic_stripe_patterns_sphere_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    StripedPattern stripes(orange, blue);
    Sphere striped_sphere;
    striped_sphere.material.set_pattern(stripes);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.push_back(striped_sphere);
    world.lights.push_back(light);

    int factor = 8;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10.5, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_gradient_patterns_sphere_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    GradientPattern gradient(orange, blue);
    Sphere gradient_sphere;
    gradient_sphere.material.set_pattern(gradient);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.push_back(gradient_sphere);
    world.lights.push_back(light);

    int factor = 8;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10.5, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_ring_patterns_sphere_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();


    // patterns
    RingPattern ring(orange, blue);
    ring.set_transform(Transformation::scaling(0.1));
    Sphere ring_sphere;
    ring_sphere.material.set_pattern(ring);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.push_back(ring_sphere);
    world.lights.push_back(light);

    int factor = 8;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10.5, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_checker_pattern_sphere_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();


    // patterns
    CheckerPattern checker(orange, blue);
    Sphere checker_sphere;
    checker_sphere.material.set_pattern(checker);

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.push_back(checker_sphere);
    world.lights.push_back(light);

    int factor = 6;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10.5, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_blended_pattern_plane_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    // patterns
    RadialGradientPattern radialgrad(orange, blue);
    StripedPattern stripes(orange, blue);
    Plane plane;
    plane.material.add_pattern(radialgrad);
    plane.material.add_pattern(stripes);

    // light
    PointLight light(Tuple::point(0, 10, 0), Color::white());

    // world
    World world;
    world.planes.insert(world.planes.end(), {plane} );
    world.lights.push_back(light);

    int factor = 8;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 10, -10),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_blended_sphere_patterns_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    Color red = Color::red();
    Color yellow = Color::yellow();

    // patterns
    StripedPattern stripes(orange, blue);
    StripedPattern stripes_rot(red, yellow);
    GradientPattern gradient(orange, blue);
    RingPattern rings(orange, blue);
    CheckerPattern checkers(orange, blue);

    stripes.set_transform(Transformation::scaling(0.1));
    stripes_rot.set_transform(Transformation::rotation_y(M_PI_2) * Transformation::scaling(0.1));
    gradient.set_transform(Transformation::scaling(2, 1, 1) * Transformation::translation(0.5, 0, 0));
    rings.set_transform(Transformation::scaling(0.085));
    checkers.set_transform(Transformation::scaling(0.25));

    // Shapes
    Sphere striped_sphere;
    Sphere gradient_sphere;
    Sphere ring_sphere;
    Sphere checkered_sphere;

    Plane regular_plane;
    Plane striped_plane;
    Plane gradient_plane;
    Plane ring_plane;
    Plane checkered_plane;

//    striped_sphere.set_transform(Transformation::translation(-2.25, 0, 1) * Transformation::scaling(.6));
//    gradient_sphere.set_transform(Transformation::translation(-0.75, 0, 1) * Transformation::scaling(.6));
//    ring_sphere.set_transform(Transformation::translation(.75, 0, 1) * Transformation::scaling(.6));
//    checkered_sphere.set_transform(Transformation::translation(2.25, 0, 1) * Transformation::scaling(.6));
    float sphere_size = .9;
    float delta = 2.2;
    float two = -delta / 2;
    float three = delta / 2;
    float one = two - delta;
    float four = three + delta;

    float y_up = 0;
    striped_sphere.set_transform(Transformation::translation(one, y_up, 1) * Transformation::scaling(sphere_size));
    gradient_sphere.set_transform(Transformation::translation(two, y_up, 1) * Transformation::scaling(sphere_size));
    ring_sphere.set_transform(Transformation::translation(three, y_up, 1) * Transformation::scaling(sphere_size));
    checkered_sphere.set_transform(Transformation::translation(four, y_up, 1) * Transformation::scaling(sphere_size));

    striped_sphere.material.set_pattern(stripes);
    gradient_sphere.material.set_pattern(gradient);
    ring_sphere.material.set_pattern(rings);
    checkered_sphere.material.set_pattern(checkers);

    striped_sphere.material.add_pattern(stripes_rot);
    gradient_sphere.material.add_pattern(stripes_rot);
    ring_sphere.material.add_pattern(stripes_rot);
    checkered_sphere.material.add_pattern(stripes_rot);

    regular_plane.set_transform(Transformation::translation(0, -1, 0));
//    striped_plane;
//    gradient_plane;
//    ring_plane;
//    checkered_plane;

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.insert(world.spheres.end(), {striped_sphere, gradient_sphere, ring_sphere, checkered_sphere} );
    world.planes.push_back(regular_plane);
//    world.planes.insert(world.planes.end(), {striped_plane, gradient_plane, ring_plane, checkered_plane} );
    world.lights.push_back(light);

    int factor = 10;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 4., -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void default_world_w_reflection(){
    World w = World::DefaultWorld();

    Plane p;
    p.name = std::string("p");
    p.material.reflective = 0.5;
    p.set_transform(Transformation::translation(0, -1, 0));
    w.planes.push_back(p);

    int factor = 10;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 4., -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, w);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void basic_blended_sphere_patterns_with_reflections_example(){
    // colors
    Color orange = Color(1, .27, 0, 1);
    Color blue = Color::blue();

    Color red = Color::red();
    Color yellow = Color::yellow();

    // patterns
    StripedPattern stripes(orange, blue);
    StripedPattern stripes_rot(red, yellow);
    GradientPattern gradient(orange, blue);
    RingPattern rings(orange, blue);
    CheckerPattern checkers(orange, blue);

    stripes.set_transform(Transformation::scaling(0.1));
    stripes_rot.set_transform(Transformation::rotation_y(M_PI_2) * Transformation::scaling(0.1));
    gradient.set_transform(Transformation::scaling(2, 1, 1) * Transformation::translation(0.5, 0, 0));
    rings.set_transform(Transformation::scaling(0.085));
    checkers.set_transform(Transformation::scaling(0.25));

    // Shapes
    Sphere striped_sphere;
    Sphere gradient_sphere;
    Sphere ring_sphere;
    Sphere checkered_sphere;

    float sphere_size = .9;
    float delta = 2.2;
    float two = -delta / 2;
    float three = delta / 2;
    float one = two - delta;
    float four = three + delta;

    float y_up = 0;
    striped_sphere.set_transform(Transformation::translation(one, y_up, 1) * Transformation::scaling(sphere_size));
    gradient_sphere.set_transform(Transformation::translation(two, y_up, 1) * Transformation::scaling(sphere_size));
    ring_sphere.set_transform(Transformation::translation(three, y_up, 1) * Transformation::scaling(sphere_size));
    checkered_sphere.set_transform(Transformation::translation(four, y_up, 1) * Transformation::scaling(sphere_size));

    striped_sphere.material.set_pattern(stripes);
    gradient_sphere.material.set_pattern(gradient);
    ring_sphere.material.set_pattern(rings);
    checkered_sphere.material.set_pattern(checkers);

//    striped_sphere.material.add_pattern(stripes_rot);
//    gradient_sphere.material.add_pattern(stripes_rot);
//    ring_sphere.material.add_pattern(stripes_rot);
//    checkered_sphere.material.add_pattern(stripes_rot);


    float ref = 0.5;
    striped_sphere.material.reflective = 0.1;
    gradient_sphere.material.reflective = 0.2;
    ring_sphere.material.reflective = 0.3;
    checkered_sphere.material.reflective = 0.4;

    Plane regular_plane;
    regular_plane.set_transform(Transformation::translation(0, -1, 0));
    CheckerPattern checkerPlanePattern(Color::white(), Color::black());
    regular_plane.material.set_pattern(checkerPlanePattern);
    regular_plane.material.reflective = ref;

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.insert(world.spheres.end(), {striped_sphere, gradient_sphere, ring_sphere, checkered_sphere} );
    world.planes.push_back(regular_plane);
//    world.planes.insert(world.planes.end(), {striped_plane, gradient_plane, ring_plane, checkered_plane} );
    world.lights.push_back(light);

    int factor = 10;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 4., -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world, true, 1);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void perfectly_reflective_spheres(){
    Sphere s1;
    Sphere s2;
    Sphere s3;
    Sphere s4;

    float sphere_size = .9;
    float delta = 2.2;
    float two = -delta / 2;
    float three = delta / 2;
    float one = two - delta;
    float four = three + delta;

    float y_up = 0;
    s1.set_transform(Transformation::translation(one, y_up, 1) * Transformation::scaling(sphere_size));
    s2.set_transform(Transformation::translation(two, y_up, 1) * Transformation::scaling(sphere_size));
    s3.set_transform(Transformation::translation(three, y_up, 1) * Transformation::scaling(sphere_size));
    s4.set_transform(Transformation::translation(four, y_up, 1) * Transformation::scaling(sphere_size));

    s1.material.color = Color::black();
    s2.material.color = Color::black();
    s3.material.color = Color::black();
    s4.material.color = Color::black();

    float ref = 1;
    s1.material.reflective = ref;
    s2.material.reflective = ref;
    s3.material.reflective = ref;
    s4.material.reflective = ref;

    Plane regular_plane;
    regular_plane.set_transform(Transformation::translation(0, -1, 0));
    CheckerPattern checkerPlanePattern(Color::white(), Color::black());
    regular_plane.material.set_pattern(checkerPlanePattern);
    regular_plane.material.reflective = ref;

    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.insert(world.spheres.end(), {s1, s2, s3, s4} );
    world.planes.push_back(regular_plane);
//    world.planes.insert(world.planes.end(), {striped_plane, gradient_plane, ring_plane, checkered_plane} );
    world.lights.push_back(light);

    int factor = 30;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 4., -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void challenge_plane_w_reflections(){
    Plane floor;
    Plane ceiling;
    Plane back_wall;
    Plane front_wall;
    Plane left_wall;
    Plane right_wall;

    ceiling.set_transform(Transformation::translation(0, 11, 0) * Transformation::rotation_x(M_PI));
    back_wall.set_transform(Transformation::translation(0, 0, 3) * Transformation::rotation_x(M_PI_2));
    front_wall.set_transform(Transformation::translation(0, 0, -11) * Transformation::rotation_x(-M_PI_2));
    left_wall.set_transform(Transformation::translation(-11, 0, 0) * Transformation::rotation_z(M_PI_2));
    right_wall.set_transform(Transformation::translation(11, 0, 0) * Transformation::rotation_z(M_PI_2));

    Color red = Color::red();
    Color green = Color::green();
    Color blue = Color::blue();
    Color white = Color::white();
    floor.material.add_pattern(CheckerPattern(red, white));
    ceiling.material.add_pattern(CheckerPattern(red, white));
    back_wall.material.add_pattern(CheckerPattern(green, white));
    front_wall.material.add_pattern(CheckerPattern(green, white));
    left_wall.material.add_pattern(CheckerPattern(blue, white));
    right_wall.material.add_pattern(CheckerPattern(blue, white));

    floor.material.reflective = .1;
    ceiling.material.reflective = .1;
    back_wall.material.reflective = .1;
    front_wall.material.reflective = .1;
    left_wall.material.reflective = .1;
    right_wall.material.reflective = .1;

    Sphere redDome;
    redDome.set_transform(Transformation::translation(-1.5, .8, 1) * Transformation::scaling(0.35));
    redDome.material.color = Color(1, 0.2, 0.1, 1);
    redDome.material.diffuse = 0.7;
    redDome.material.specular = 0.8;
    redDome.material.reflective = 1;

    Sphere blueDisk;
    blueDisk.set_transform(
            Transformation::translation(-1.5, .8, 1) *
            Transformation::rotation_x(-M_PI_4) *
            Transformation::rotation_z(-M_PI / 5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    blueDisk.material.color = Color(0.3, 0.2, 1, 1);
    blueDisk.material.diffuse = 0.7;
    blueDisk.material.specular = 0.8;
    blueDisk.material.shininess = 200;
    blueDisk.material.reflective = .2;

    Sphere blueDome;
    blueDome.set_transform(Transformation::translation(1.5, 1.5, 1.3) * Transformation::scaling(0.35));
    blueDome.material.color = Color(0.3, 0.2, 1, 1);
    blueDome.material.diffuse = 0.7;
    blueDome.material.specular = 0.8;
    blueDome.material.reflective = .2;

    Sphere redDisk;
    redDisk.set_transform(
            Transformation::translation(1.5, 1.5, 1.3) *
            Transformation::rotation_y(-M_PI / 3) *
            Transformation::rotation_z(M_PI / 2.5) *
            Transformation::scaling(0.8, 0.1, 0.8)
    );
    redDisk.material.color = Color(1, 0.2, 0.1, 1);
    redDisk.material.diffuse = 0.7;
    redDisk.material.specular = 0.8;
    redDisk.material.shininess = 200;
    redDisk.material.reflective = .2;

    Sphere origin;
    origin.set_transform(Transformation::scaling(0.5));
    origin.material.reflective = 1;

    // Set Lighting
    PointLight l1(Tuple::point(-10, 10, -10), Color::white());
    PointLight l2(Tuple::point(-5, 10, -10), Color::white());
    PointLight l3(Tuple::point(-0, 10, -10), Color::white());
    PointLight l4(Tuple::point(5, 10, -10), Color::white());
    PointLight l5(Tuple::point(0, 10, 0), Color::white());
    PointLight l6(Tuple::point(0, 10, -1), Color::white());

    // Set World
    World world;

    world.spheres.insert(world.spheres.end(), {origin, redDome, blueDisk, blueDome, redDisk} );

    world.planes.insert(world.planes.end(), {floor, ceiling, back_wall, front_wall, left_wall, right_wall});//, front_wall, left_wall, right_wall});
//    world.planes.insert(world.planes.end(), {floor, back_wall});

    world.lights.push_back(l1);
//    world.lights.push_back(l2);
//    world.lights.push_back(l3);
//    world.lights.push_back(l4);
//    world.lights.push_back(l5);
//    world.lights.push_back(l6);

    // Set Camera
    int factor = 6;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 1.5, -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world, true, 3);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);


}

void glass_spheres(){
    Plane floor;
    Plane ceiling;
    Plane back_wall;
    Plane front_wall;
    Plane left_wall;
    Plane right_wall;

    ceiling.set_transform(Transformation::translation(0, 11, 0) * Transformation::rotation_x(M_PI));
    back_wall.set_transform(Transformation::translation(0, 0, 6) * Transformation::rotation_x(M_PI_2));
    front_wall.set_transform(Transformation::translation(0, 0, -11) * Transformation::rotation_x(-M_PI_2));
    left_wall.set_transform(Transformation::translation(-11, 0, 0) * Transformation::rotation_z(M_PI_2));
    right_wall.set_transform(Transformation::translation(11, 0, 0) * Transformation::rotation_z(M_PI_2));

    Color red = Color::red();
    Color green = Color::green();
    Color blue = Color::blue();
    Color white = Color::white();
    floor.material.add_pattern(CheckerPattern(red, white));
    ceiling.material.add_pattern(CheckerPattern(red, white));
    back_wall.material.add_pattern(CheckerPattern(green, white));
    front_wall.material.add_pattern(CheckerPattern(green, white));
    left_wall.material.add_pattern(CheckerPattern(blue, white));
    right_wall.material.add_pattern(CheckerPattern(blue, white));

//    floor.material.reflective = .1;
//    ceiling.material.reflective = .1;
//    back_wall.material.reflective = .1;
//    front_wall.material.reflective = .1;
//    left_wall.material.reflective = .1;
//    right_wall.material.reflective = .1;

    // Shapes
    Sphere s1;
    Sphere s2;
    Sphere s3;
    Sphere s4;
    Sphere s2_in;
    Sphere s4_in;

    float sphere_size = .9;
    float delta = 2.2;
    float two = -delta / 2;
    float three = delta / 2;
    float one = two - delta;
    float four = three + delta;

    float y_up = 1;
    s1.set_transform(Transformation::translation(one, y_up, 1) * Transformation::scaling(sphere_size));
    s2.set_transform(Transformation::translation(two, y_up, 1) * Transformation::scaling(sphere_size));
    s3.set_transform(Transformation::translation(three, y_up, 1) * Transformation::scaling(sphere_size));
    s4.set_transform(Transformation::translation(four, y_up, 1) * Transformation::scaling(sphere_size));

    s2_in.set_transform(Transformation::translation(two, y_up, 1) * Transformation::scaling(sphere_size-0.04));
    s4_in.set_transform(Transformation::translation(four, y_up, 1) * Transformation::scaling(sphere_size-0.04));

    s1.material.color = Color::black();
    s2.material.color = Color::black();
    s3.material.color = Color::black();
    s4.material.color = Color::black();
    s2_in.material.color = Color::black();
    s4_in.material.color = Color::black();
    auto rings = RingPattern(Color::orange(), Color::blue());
    rings.set_transform(Transformation::rotation_x(-M_PI_2/2) * Transformation::scaling(0.05));
    s2.material.set_pattern(rings);
    s3.material.set_pattern(rings);

    s1.material.transparency = 1;
    s2.material.transparency = .8;
    s3.material.transparency = .7;
    s4.material.transparency = 1;
    s2_in.material.transparency = 1;
    s4_in.material.transparency = 1;

    s1.material.refractive_index = 1.5;
    s2.material.refractive_index = 1.5;
    s3.material.refractive_index = 1.5;
    s4.material.refractive_index = 1.5;
    s2_in.material.refractive_index = 1.;
    s4_in.material.refractive_index = 1.;

    s1.material.reflective = 1;
    s2.material.reflective = 1;
    s3.material.reflective = 1;
    s4.material.reflective = 1;
    s2_in.material.reflective = 1;
    s4_in.material.reflective = 1;

//    Sphere orb;
    s1.material.diffuse = 0.1;
    s2.material.diffuse = 0.3;
    s3.material.diffuse = 0.3;
    s4.material.diffuse = 0.1;
    s1.material.ambient = 0.1;
    s2.material.ambient = 0.1;
    s3.material.ambient = 0.1;
    s4.material.ambient = 0.1;
    s1.material.specular = 1;
    s2.material.specular = 1;
    s3.material.specular = 1;
    s4.material.specular = 1;
    s1.material.shininess = 300;
    s2.material.shininess = 300;
    s3.material.shininess = 300;
    s4.material.shininess = 300;
    s2_in.material.diffuse = 0.1;
    s4_in.material.diffuse = 0.1;
    s2_in.material.ambient = 0.1;
    s4_in.material.ambient = 0.1;
    s2_in.material.specular = 1;
    s4_in.material.specular = 1;
    s2_in.material.shininess = 300;
    s4_in.material.shininess = 300;


    PointLight light(Tuple::point(0, 10, 0), Color::white());

    World world;
    world.spheres.insert(world.spheres.end(), {s1, s2, s3, s4} );
    world.spheres.insert(world.spheres.end(), {s2_in, s4_in} );
    world.planes.insert(world.planes.end(), {floor, ceiling, back_wall, front_wall, left_wall, right_wall});//, front_wall, left_wall, right_wall});
    world.lights.push_back(light);

    int factor = 60;
    Camera camera(100*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 4., -5),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );
//    camera.set_transform(
//            Transformation::view_transform(
//                    Tuple::point(two, 5., 1),
//                    Tuple::point(two, 1, 1),
//                    Tuple::vector(0, 0, 1)
//            )
//    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world, false, 5);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void single_simple_glass_sphere_checkered_floor(){
    Plane floor;
    floor.material.add_pattern(CheckerPattern(Color::blue(), Color::white()));

    Plane ceiling;
    ceiling.set_transform(Transformation::translation(0, 15, 0));
    ceiling.material.add_pattern(RingPattern(Color::red(), Color::blue()));

    Sphere orb;
    orb.material.color = Color::black();
    orb.set_transform(Transformation::translation(0, 1.01, 0));
    orb.material.transparency = 1;
    orb.material.refractive_index = 1.5;
    orb.material.reflective = 1;
    orb.material.diffuse = 0.1;
    orb.material.ambient = 0.1;
    orb.material.specular = 1;
    orb.material.shininess = 300;

    Sphere inner;
    inner.material.color = Color::black();
    inner.set_transform(Transformation::translation(0, 1.01, 0) * Transformation::scaling(0.5));
    inner.material.transparency = 1;
    inner.material.refractive_index = 1.0;
    inner.material.reflective = 1;

    PointLight light(Tuple::point(10, 10, -10), Color::white());

    World world;
    world.spheres.insert(world.spheres.end(), {orb, inner} );
    world.planes.insert(world.planes.end(), {floor});
    world.lights.push_back(light);

    int factor = 30;
    Camera camera(50*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 3, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );

//    camera.set_transform(
//            Transformation::view_transform(
//                    Tuple::point(0, 2, -4),
//                    Tuple::point(0, 1, 0),
//                    Tuple::vector(0, 1, 0)
//            )
//    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world, false, 5);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void water_rocks(){
    World world;

    Plane sky;
    sky.set_transform(Transformation::translation(0, 20, 0));
    sky.material.color = Color::cyan();

    Plane water;
    water.casts_shadow = false;
    water.material.transparency = 1;
    water.material.refractive_index = 1.33;
//    water.material.color = 1;
    water.material.reflective = 0;
    water.material.diffuse = 0.;
    water.material.ambient = 0.;
    water.material.specular = 1;
    water.material.shininess = 300;
    water.set_transform(Transformation::translation(0, 1.01, 0));
    world.planes.insert(world.planes.end(), {water, sky});

    Sphere rock1;
    Sphere rock2;
    Sphere rock3;
    Sphere rock4;
    rock1.material.color = Color::red();
    rock2.material.color = Color::green();
    rock3.material.color = Color::blue();
    rock4.material.color = Color::orange();
    rock1.set_transform(Transformation::translation(-1, 0, -1));
    rock2.set_transform(Transformation::translation(-1, 0, 1));
    rock3.set_transform(Transformation::translation(1, 0, -1));
    rock4.set_transform(Transformation::translation(1, 0, 1));
//    world.spheres.insert(world.spheres.end(), {rock2});
    world.spheres.insert(world.spheres.end(), {rock1, rock2, rock3, rock4} );


    PointLight light(Tuple::point(10, 10, -10), Color::white());
    world.lights.push_back(light);

//    Sphere center;
//    world.spheres.push_back(center);

    int factor = 10;
    Camera camera(50*factor, 50*factor, M_PI/3.f);
    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 6, 0),
                    Tuple::point(0, 0, 0),
                    Tuple::vector(0, 0, 1)
            )
    );

    camera.set_transform(
            Transformation::view_transform(
                    Tuple::point(0, 2, -4),
                    Tuple::point(0, 1, 0),
                    Tuple::vector(0, 1, 0)
            )
    );

    auto start = std::chrono::high_resolution_clock::now();

    Canvas canvas = Canvas::render(camera, world, true, 5);

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    std::cout << "render Time: " << duration.count() << " seconds" << std::endl;

    std::string filename = "../exported_images/canvas_";
    filename.append(__FUNCTION__);
    filename.append("_" + std::to_string(duration.count()) + "s");
    canvas.to_ppm_file(filename);
}

void glass_spheres_class(){
    auto world = World();

    auto pointlight = PointLight(Tuple::point(10, 10, -10), Color::white());
    world.add(pointlight);

    auto plane = Plane();
    auto checkers = CheckerPattern();
//    checkers.set_transform(Transformation::scaling(0.66));
    plane.material.set_pattern(checkers);
    plane.set_transform(Transformation::translation(0, -1.01, 0));
    world.add(plane);

    auto hgs_front = HollowGlassSphere();
    hgs_front.set_color(Color::maroon());
    world.add(hgs_front);

    int factor = 10;
    Camera camera = Camera::unit_sphere_plane_elevation(50*factor, 50*factor);
//    Camera camera = Camera::unit_sphere_plane_angled(50*factor, 50*factor);
//    Camera camera = Camera::unit_sphere_plane_birds_eye(50*factor, 50*factor);

    render_time_and_save(camera, world, true, 4, __FUNCTION__);
}

void glass_spheres_recursive(){
    auto world = World();

    auto pointlight = PointLight(Tuple::point(10, 5, -10), Color::white());
    world.add(pointlight);

    auto plane = Plane();
    auto checkers = CheckerPattern();
    plane.material.set_pattern(checkers);
    plane.set_transform(Transformation::translation(0, -1.01, 0));
    world.add(plane);

    auto hgs0 = HollowGlassSphere();
    auto hgs1 = HollowGlassSphere();
    auto hgs2 = HollowGlassSphere();
    auto hgs3 = HollowGlassSphere();
    auto hgs4 = HollowGlassSphere();

    hgs1.set_transform(Transformation::translation(-0.30, 0.00, -0.30) * Transformation::scaling(0.85));
    hgs2.set_transform(Transformation::translation(0.20, 0.20, 0.20) * Transformation::scaling(0.7));
//    hgs3.set_transform(Transformation::translation(0.00, 0.00, 0.00) * Transformation::scaling(0.4));
//    hgs4.set_transform(Transformation::translation(0.00, 0.00, 0.00) * Transformation::scaling(0.2));

    world.add(hgs0);
    world.add(hgs1);
    world.add(hgs2);
//    world.add(hgs3);
//    world.add(hgs4);

    int factor = 20;
    Camera camera_elv = Camera::unit_sphere_plane_elevation(50*factor, 50*factor);
    Camera camera_ang = Camera::unit_sphere_plane_angled(50*factor, 50*factor);
    Camera camera_bird = Camera::unit_sphere_plane_birds_eye(50*factor, 50*factor);

    // num refractions needs to be 2 * num overlapping spheres. each hollow glass is 2 spheres. so 4 * num hgs;
//    render_time_and_save(camera_elv, world, true, 2 * world.spheres.size(), __FUNCTION__);
//    render_time_and_save(camera_elv, world, false, 2 * world.spheres.size(), __FUNCTION__);
//    render_time_and_save(camera_ang, world, true, 2 * world.spheres.size(), __FUNCTION__);
    render_time_and_save(camera_ang, world, false, 2 * world.spheres.size(), __FUNCTION__);
//    render_time_and_save(camera_bird, world, true, 2 * world.spheres.size(), __FUNCTION__);
    render_time_and_save(camera_bird, world, false, 2 * world.spheres.size(), __FUNCTION__);

}

int main()
{
//    challenge_world_w_spheres();
//    custom_scene();
//    challenge_plane();
//    non_transformed_patterns();
//    transformed_patterns();

//    basic_sphere_patterns_example();
//
//    basic_stripe_patterns_plane_example();
//    basic_gradient_patterns_plane_example();
//    basic_ring_patterns_plane_example();
//    basic_checker_pattern_plane_example();
//    basic_blended_pattern_plane_example();
//    basic_blended_sphere_patterns_example();
//    basic_blended_sphere_patterns_with_reflections_example();
//    perfectly_reflective_spheres();
//    default_world_w_reflection();
//
//    basic_stripe_patterns_sphere_example();
//    basic_gradient_patterns_sphere_example();
//    basic_ring_patterns_sphere_example();
//    basic_checker_pattern_sphere_example();

//    challenge_plane_w_reflections();
//    glass_spheres();
//    single_simple_glass_sphere_checkered_floor();
//    water_rocks();
    glass_spheres_class();
//    glass_spheres_recursive();
    return 0;
}