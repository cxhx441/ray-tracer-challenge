//
// Created by Craig Harris on 7/27/24.
//

#ifndef RAYTRACERCHAELLENGE_CANVAS_H
#define RAYTRACERCHAELLENGE_CANVAS_H

#include "tuple.h"

class Canvas {
public:
    int width;
    int height;
    Color** pixels;

    Canvas(int width, int height);
    ~Canvas();
    void FillPixels(const Color& color);
    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas); // for printing
};


#endif //RAYTRACERCHAELLENGE_CANVAS_H
