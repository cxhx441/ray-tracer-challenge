//
// Created by Craig Harris on 7/27/24.
//

#ifndef RAYTRACERCHAELLENGE_CANVAS_H
#define RAYTRACERCHAELLENGE_CANVAS_H

#include "Tuple.h"
#include <string>

class Canvas {
public:
    int width;
    int height;
    Tuple** pixels;

    Canvas(int width, int height);
    ~Canvas();
    void FillPixels(const Tuple& color);
    void WritePixel(int x, int y, const Tuple& color);
    std::string ToPPMString();
    void ToPPMFile(std::string title);
    static int MapColorValue(float colorVal, int maxValue);
    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas); // for printing
};


#endif //RAYTRACERCHAELLENGE_CANVAS_H
