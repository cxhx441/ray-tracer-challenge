//
// Created by Craig Harris on 7/27/24.
//

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(int width, int height) : width(width), height(height){
    pixels = new Color*[height];
    for (int h = 0; h < height; ++h){
        pixels[h] = new Color[width];
    }
    FillPixels(Color(0, 0, 0, 1));
};

Canvas::~Canvas() {
    // Free the allocated memory
    for (int h = 0; h < height; ++h) {
        delete[] pixels[h];
    }
    delete[] pixels;
}

void Canvas::FillPixels(const Color& color){
    for (int h = 0; h < height; ++h){
        for (int w = 0; w < width; ++w){
            pixels[h][w] = color;
        }
    }
}


std::ostream& operator<<(std::ostream& os, const Canvas& canvas) {
    for (int h = 0; h < canvas.height; ++h) {
        for (int w = 0; w < canvas.width; ++w) {
            Color c = canvas.pixels[h][w];
            os << "(" << c.r() << ", " << c.g() << ", " << c.b() << ", " << c.a() << ") ";
        }
        os << std::endl;
    }
    return os;
}
