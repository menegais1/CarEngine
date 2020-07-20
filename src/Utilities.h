///Utilities file, has some common structs and functions used in the program

#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include "Vectors/Vector2.h"
#include "Vectors/Vector3.h"
#include "Vectors/Vector4.h"

#define PI        3.14159265358979323846    /* pi */

enum Channel {
    Red = 0,
    Green = 1,
    Blue = 2,
    Alpha = 3
};

enum MouseButton {
    Left = 0,
    ScrollClick = 1,
    Right = 2,
    ScrollUp = 3,
    ScrollDown = 4
};

enum MouseState {
    Down = 0,
    Up = 1,
    None = -2
};

bool isPointInsideBounds(dvec2 point, dvec2 position, dvec2 scale);

bool isPointInsideCircle(dvec2 point, dvec2 center, float radius);

int isLeft(dvec3 P0, dvec3 P1, dvec3 P2);

bool isPointInsidePolygon(dvec2 P, std::vector<dvec3> vertices, int n);

std::vector<dvec3> generateSquare(dvec3 center, dvec3 scale);

std::vector<dvec3> generateCircle(dvec3 center, dvec3 scale, float sides);

std::vector<dvec3> generateTriangle(dvec3 center, dvec3 scale);

std::vector<dvec3> generatePentagon(dvec3 center, dvec3 scale);

std::vector<dvec3> generateHexagon(dvec3 center, dvec3 scale);

dvec2 getMaximumAbsValue(std::vector<dvec2> values);

dvec2 getMaximumValue(std::vector<dvec2> values);

dvec2 getMinimumValue(std::vector<dvec2> values);

bool leftMouseDown(int button, int state);

bool leftMouseUp(int button, int state);

dvec3 lerp(dvec3 x0, dvec3 x1, float t);

float lerp(float v0, float v1, float t);

float clamp(float v0, float v1, float v);

float round(float v0, float v1, float v);

dvec3 RandomColorGenerator(float saturation, float brightness);

dvec3 HSVtoRGB(dvec3 hsv);

dvec2 rotatePoint2D(dvec2 point, float angle);

#endif
