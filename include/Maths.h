#pragma once
#define _USE_MATH_DEFINES

#include <iostream> 
#include <limits>
#include <cmath>

#include "Vec2.h"

constexpr float FLOAT_MIN = std::numeric_limits<float>::min();

double degreesToRadians(double d) {
    return d * M_PI/180;
}

// rotation d'un point selon l'origine
// x' = x*cos(TH) - y*sin(TH)
// y' = x*sin(TH) + y*cos(TH)
// Si on précise pas origine alors origine = vraie origine (top left)
//FIXME: inverser rotation ? par rapport au fait qu'origine == top left
/**
 * @brief Rotation of a point about another point
 * 
 * @param v vector we want to rotate
 * @param rotationDegree the rotation angle in degree
 * @param origin the rotation point (from where we are rotating the point)
 */
void rotate(Vec2& v, float rotationDegree, const Vec2& origin = Vec2{0,0}) {
    // mise à l'échelle (on remet x et y à l'origine)
    float x = v.x - origin.x;
    float y = v.y - origin.y;

    float rotRadians = degreesToRadians(rotationDegree);
    float cosA = (float) cos(rotRadians);
    float sinA = (float) sin(rotRadians);

    float x1 = (x * cosA) - (y * sinA);
    float y1 = (x * sinA) + (y * cosA);
    x1 += origin.x;
    y1 += origin.y;

    v.x = x1;
    v.y = y1;
}

bool compare(float x, float y, float epsilon = FLOAT_MIN) {
    return fabs(x - y) <= epsilon * (std::max((double) 1.0f, std::max(fabs(x), fabs(y))));
}

bool compare(const Vec2& v1, const Vec2& v2, float epsilon = FLOAT_MIN) {
    return compare(v1.x, v2.x, epsilon) && compare(v1.y, v2.y, epsilon);
}

// bool compare(float x, float y) {return false;}