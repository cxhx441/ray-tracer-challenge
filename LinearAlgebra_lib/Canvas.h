//
// Created by Craig Harris on 7/27/24.
//

#ifndef RAYTRACERCHAELLENGE_CANVAS_H
#define RAYTRACERCHAELLENGE_CANVAS_H

#include "Tuple.h"

class Canvas {
public:
    int width;
    int height;
    Tuple** pixels;

    Canvas(int width, int height);
    ~Canvas();
    void FillPixels(const Tuple& color);
    void WritePixel(int x, int y, const Tuple& color);
    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas); // for printing
};


#endif //RAYTRACERCHAELLENGE_CANVAS_H
