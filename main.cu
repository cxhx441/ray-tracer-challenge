#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Transformation.h"
#include "Sphere.h"
#include "Intersection.h"
#include <filesystem>
#include <cmath>

#include <math_constants.h>
#include <cuda_runtime.h>

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
    // Matrix R = Transformation::rotation_z(2.f * (355.f/113.f) / numVertices);
    Matrix R = Transformation::rotation_z(2.f * (CUDART_PI) / numVertices);
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

void challenge_ray_to_sphere(){
    float backdrop_z = 10.f;
    float backdrop_size = 7.f;
    float backdrop_half_size = backdrop_size / 2.f;
    int canvas_size = 64;
    float pixel_size = (float) backdrop_size / (float) canvas_size;
    Tuple color = Tuple::color(1, 0, 0, 1);
    Canvas canvas(canvas_size, canvas_size);

    Sphere s;
    Matrix shear = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix rot = Transformation::rotation_y((355.f/113.f) / 2.f);
    Matrix scale = Transformation::scaling(0.75f);
    s.transformation = scale * rot * shear;

    Tuple origin = Tuple::point(0, 0, -5);
    Ray r(origin, Tuple::vector(0, 0, 0));

    for (int y = 0; y < canvas_size; ++y) {
        float world_y = backdrop_half_size - ( pixel_size * y );
        for (int x = 0; x < canvas_size; ++x) {
            float world_x = -backdrop_half_size + ( pixel_size * x );
            Tuple target = Tuple::point(world_x, world_y, backdrop_z);
            r.direction = Tuple::normalize(target - r.origin);
            std::vector<Intersection> xs = Intersection::Intersect(s, r);
            Intersection* h = Intersection::Hit(xs);
            if (h) {
                try { canvas.WritePixel(x, y, color); }
                catch (std::invalid_argument const &ex) { std::cout << ex.what() << std::endl; };
            }
        }
    }
    canvas.ToPPMFile("../../canvas");
}

__global__ void render_kernel(Canvas canvas, Sphere s, Ray r, float backdrop_z, float backdrop_half_size, float pixel_size, Tuple color){
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int canvas_size = canvas.width;

    if (x < canvas_size && y < canvas_size) {
        float world_y = backdrop_half_size - (pixel_size * y);
        float world_x = -backdrop_half_size + (pixel_size * x);
//        Tuple ToTarget = Tuple::vector(world_x - r.origin.x, world_y - r.origin.y, backdrop_z - r.origin.z);
        Tuple target = Tuple::point(world_x, world_y, backdrop_z);
        r.direction = Tuple::normalize( target - r.origin);

        std::vector<Intersection> xs = Intersection::Intersect(s, r);
        Intersection *h = Intersection::Hit(xs);
        if (h) {
            canvas.WritePixel(x, y, color);
        }
    }
}

void challenge_ray_to_sphere_CUDA(){
    float backdrop_z = 10.f;
    float backdrop_size = 7.f;
    float backdrop_half_size = backdrop_size / 2.f;
    int canvas_size = 64;
    float pixel_size = (float) backdrop_size / (float) canvas_size;
    Tuple color = Tuple::color(1, 0, 0, 1);
    Canvas canvas(canvas_size, canvas_size);

    Sphere s;
    Matrix shear = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix rot = Transformation::rotation_y((355.f/113.f) / 2.f);
    Matrix scale = Transformation::scaling(0.75f);
    s.transformation = scale * rot * shear;

    Tuple origin = Tuple::point(0, 0, -5);
    Ray r(origin, Tuple::vector(0, 0, 0));

    // Define CUDA grid and block sizes
    dim3 blockSize(16, 16);
    dim3 gridSize((canvas_size + blockSize.x - 1) / blockSize.x, (canvas_size + blockSize.y - 1) / blockSize.y);

    Canvas* d_canvas;
    Sphere* d_sphere;
    Tuple* d_ray;
    Tuple* d_color;

    cudaMalloc(&d_canvas, sizeof (Canvas));
    cudaMalloc(&d_sphere, sizeof (Sphere));
    cudaMalloc(&d_ray, sizeof (Ray));
    cudaMalloc(&d_color, sizeof (Tuple));

    cudaMemcpy(d_canvas, &canvas, sizeof (Canvas), cudaMemcpyHostToDevice);
    cudaMemcpy(d_sphere, &s, sizeof (Sphere), cudaMemcpyHostToDevice);
    cudaMemcpy(d_ray, &r, sizeof (Ray), cudaMemcpyHostToDevice);
    cudaMemcpy(d_color, &color, sizeof (Tuple), cudaMemcpyHostToDevice);

    // Launch the kernel
    render_kernel<<<gridSize, blockSize>>>(canvas, s, r, backdrop_z, backdrop_half_size, pixel_size, color);

    // Copy the results back to host memory
    cudaMemcpy(&canvas, d_canvas, sizeof (Canvas), cudaMemcpyDeviceToHost);

    cudaFree(d_canvas);
    cudaFree(d_sphere);
    cudaFree(d_ray);
    cudaFree(d_color);

    canvas.ToPPMFile("../../canvas");
}

int main()
{
//    challenge_clock();
    challenge_ray_to_sphere();
    return 0;
}