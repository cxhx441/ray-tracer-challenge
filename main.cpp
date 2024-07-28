#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include <filesystem>

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
int main()
{
    Canvas canvas(500, 500);
    canvas.FillPixels(Tuple::color(1, 1, 0, 1));  // Fill with red color

    // Output the colors of the canvas
//    std::cout << canvas << std::endl;
//    canvas.ToPPMString();
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string filename(cwd.string() + "/canvas");
    canvas.ToPPMFile(filename);

    Tuple initialPosition = Tuple::vector(0, 0, 0);
    Tuple initialVelocity = Tuple::vector(0, 50, 0);
    Projectile proj(initialPosition, initialVelocity);

    Tuple gravity = Tuple::vector(0, -9.8, 0);
    Tuple wind = Tuple::vector(-3, 0, 0);
    Environment env(gravity, wind );


    while (proj.position.y >= 0){
        tick(&proj, &env);
        std::cout << "Projectile Pos: " << proj.position << " Projectile Vel: " << proj.velocity << std::endl;
    }
    return 0;

}