//
// Created by craig on 9/2/2024.
//

#ifndef RAYTRACERCHALLENGE_COLOR_H
#define RAYTRACERCHALLENGE_COLOR_H

#include <stdexcept>

class Color {
public:
    float r, g, b, a;

    Color();
    Color(float r, float g, float b, float a);
    Color(float r, float g, float b);

    static Color red();
    static Color green();
    static Color blue();
    static Color yellow();
    static Color magenta();
    static Color cyan();
    static Color white();
    static Color black();
    static Color silver();
    static Color gray();
    static Color maroon();
    static Color brown();
    static Color orange();
    static Color navy();


    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator-() const;
    Color operator*(float scalar) const;
    Color operator*(const Color& other) const;
    Color operator/(float scalar) const;
    Color operator/(const Color& other) const;
    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);
    Color& operator*=(float scalar);
    Color& operator/=(float scalar);
    friend std::ostream& operator<<(std::ostream& os, const Color& t); // for printing
};


#endif //RAYTRACERCHALLENGE_COLOR_H
