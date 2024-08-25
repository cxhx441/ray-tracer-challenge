//
// Created by Craig Harris on 7/27/24.
//

#ifndef RAYTRACERCHAELLENGE_CANVAS_H
#define RAYTRACERCHAELLENGE_CANVAS_H

#include "Tuple.h"
#include "Camera.h"
#include "World.h"
#include <string>

class Canvas {
public:
    int width;
    int height;
    Tuple** pixels;
    // TODO implement the big five or refactor for std::vector

    Canvas(int width, int height);
    ~Canvas();

    void FillPixels(const Tuple& color);
    void WritePixel(int x, int y, const Tuple& color);
    static Canvas Render(Camera& c, World& w);
    static int MapColorValue(float colorVal, int maxValue);

    std::string ToPPMString();
    void ToPPMFile(std::string filename);

    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas); // for printing
};


#endif //RAYTRACERCHAELLENGE_CANVAS_H
