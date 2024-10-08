//
// Created by Craig Harris on 7/27/24.
//

#ifndef RAYTRACERCHAELLENGE_CANVAS_H
#define RAYTRACERCHAELLENGE_CANVAS_H

#include "../primitives/Tuple.h"
#include "../scene/Camera.h"
#include "../scene/World.h"
#include <string>

class Canvas {
public:
    int width;
    int height;
    Color** pixels;
    // TODO implement the big five or refactor for std::vector

    Canvas(int width, int height);
    ~Canvas();

    void fill_pixels(const Color &color);
    void write_pixel(int x, int y, const Color &color);
    static Canvas render(Camera &c, World &w, bool shadows_enabled=true, int num_reflections=3);
    static int map_color_value(float colorVal, int maxValue);

    std::string to_ppm_str();
    void to_ppm_file(std::string filename);

    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas); // for printing
};


#endif //RAYTRACERCHAELLENGE_CANVAS_H
