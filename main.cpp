#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
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
    Canvas canvas(900, 550);
//    canvas.FillPixels(Tuple::color(1, 1, 1, 1));  // Fill with red color

    // Output the colors of the canvas
//    std::cout << canvas << std::endl;
//    canvas.ToPPMString();
//    canvas.ToPPMFile("../canvas");

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

    Matrix m(4, 2);
    m[1][1] = 9.5;
    std::cout << m << std::endl;

    // I = inverse(I)
    Matrix I = Matrix::Identity(4);
    std::cout << I << std::endl;
    Matrix::Inverse(I);
    std::cout << I << std::endl;

    // Mult Matrix by its Inverse
    Matrix A(4, 4);
    A.Fill(std::vector<float> {6, 4, 4, 4,
                               5, 5, 7, 6,
                               4, -9, 3, -7,
                               9, 1, 7, -6});

    Matrix A_INV = Matrix::Inverse(A);
    Matrix A_T = Matrix::Transpose(A);
    Matrix A_T_INV = Matrix::Inverse(A_T);
    Matrix A_INV_T = Matrix::Transpose(A_INV);

    std::cout << A_T_INV << std::endl;
    std::cout << A_INV_T << std::endl;
    std::cout << (A_INV_T == A_T_INV) << std::endl;
//    Matrix A_ING = Matrix::copy(A);
//    std::cout << (A_inv == A);
//    A_inv = Matrix::Inverse(A_inv);
//
//    std::cout << A << std::endl;
//    std::cout << A_inv << std::endl;
//
//    Matrix A_A_inv = A * A_inv;
//    std::cout << A_A_inv << std::endl;
//    Matrix A_A_inv2 = A_inv * A;
//    std::cout << A_A_inv2 << std::endl;
//
//    std::cout << (I == A_A_inv) << std::endl;
//    std::cout << (I == A_A_inv2) << std::endl;





    return 0;

}