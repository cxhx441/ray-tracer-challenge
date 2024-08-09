#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Transformation.h"
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
    canvas.ToPPMFile("../../canvas");

}

void challenge_clock(){
    int size = 1000;
    Canvas canvas(size, size);
    Matrix canvas_transform = Transformation::translation(size/2, size/2, 0);

    int numVertices = 12;
    Tuple p = Tuple::point(0, 0, 0);
    Matrix T = Transformation::translation(1, 0, 0);
    Matrix R = Transformation::rotation_z(2.f * (355.f/113.f) / numVertices);
    Matrix S = Transformation::scaling(size/2 - size/10);

    p = T * p;

    for (int i = 0; i < numVertices; ++i){
        p = R * p;
        Tuple Sp = S * p;
        std::cout << "Point Pos: " << Sp << std::endl;
        Tuple cp = canvas_transform * Sp;
        try{
            canvas.WritePixel(cp.x, cp.y, Tuple::color(1, 1, 1, 1));
        }
        catch(std::invalid_argument const& ex){
            std::cout << ex.what() << std::endl;
        };

    }
    canvas.ToPPMFile("../../canvas");

}


int main()
{
    challenge_clock();
    return 0;
}