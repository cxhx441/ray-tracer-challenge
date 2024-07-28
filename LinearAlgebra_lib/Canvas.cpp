//
// Created by Craig Harris on 7/27/24.
//

#include "Canvas.h"
#include <iostream>
#include <fstream>

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

void Canvas::WritePixel(int x, int y, const Tuple& color){
    if (x > width - 1 || x < 0 || y > height - 1 || y < 0) {
        throw std::invalid_argument("X or y exceeds the limits of the canvas");
    }
    pixels[y][x] = color;
}

std::string Canvas::ToPPMString(){
    /**
    P3
    width height
    255
    ...colors...
    \n
     **/
    std::string ppm;
    ppm.append("P3\n");
    ppm.append(std::to_string(width) + ' ' + std::to_string(height) + '\n');
    ppm.append("255\n");
    for (int h = 0; h < height; ++h){
        std::string s_row;
        for (int w = 0; w < width; ++w){
            Tuple& color = pixels[h][w];
            int r = MapColorValue(color.r(), 255);
            int g = MapColorValue(color.g(), 255);
            int b = MapColorValue(color.b(), 255);
            int colorRGB[3] = {r, g, b};
            for (int i : colorRGB){
                std::string s_color_val = std::to_string(i);
                if (s_row.length() + s_color_val.length() + 1 > 70) // + 1 '\n'
                {
                    ppm.append(s_row + '\n');
                    s_row.clear();
                }
                s_row.append(s_color_val + ' ');
            }
        }
        if (!s_row.empty()){
            ppm.append(s_row + '\n');
            s_row.clear();
        }
    }
    ppm.push_back('\n');
    return ppm;
}

void Canvas::ToPPMFile(std::string filename){
    // write to file
    std::string ppm = ToPPMString();
    filename.append(".ppm");
    std::ofstream out(filename);
    out << ppm;
}

int Canvas::MapColorValue(float colorVal, int maxValue){
    int MappedColorVal = (int) colorVal * maxValue;

    if (MappedColorVal <= 0)
        return 0;
    else if (MappedColorVal >= maxValue)
        return maxValue;

    return MappedColorVal;
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
