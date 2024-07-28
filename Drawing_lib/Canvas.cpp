//
// Created by Craig Harris on 7/27/24.
//

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(int width, int height) : width(width), height(height){
    pixels = new Tuple*[height];
    for (int h = 0; h < height; ++h){
        pixels[h] = new Tuple[width];
    }
    FillPixels(Tuple(0, 0, 0, 1));
};

Canvas::~Canvas() {
    // Free the allocated memory
    for (int h = 0; h < height; ++h) {
        delete[] pixels[h];
    }
    delete[] pixels;
}

void Canvas::FillPixels(const Tuple& color){
    for (int h = 0; h < height; ++h){
        for (int w = 0; w < width; ++w){
            pixels[h][w] = color;
        }
    }
}


std::ostream& operator<<(std::ostream& os, const Canvas& canvas) {
    for (int h = 0; h < canvas.height; ++h) {
        for (int w = 0; w < canvas.width; ++w) {
            Tuple c = canvas.pixels[h][w];
            os << c;
        }
        os << std::endl;
    }
    return os;
}
