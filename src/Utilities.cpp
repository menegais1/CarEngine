#include "Utilities.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "Rendering/Canvas/gl_canvas2d.h"
#include "Vectors/Vector2.h"
#include "Vectors/Vector3.h"

bool isPointInsideBounds(dvec2 point, dvec2 position, dvec2 scale) {
    return point.x < position.x + scale.x && point.x > position.x && point.y < position.y + scale.y &&
           point.y > position.y;
}

int isLeft(dvec3 P0, dvec3 P1, dvec3 P2) {
    return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}


//Crossing number point in polygon algorithm implementation
//This code is patterned after [Franklin, 2000]
//Taken from http://geomalgorithms.com/a03-_inclusion.html
bool isPointInsidePolygon(dvec2 P, std::vector<dvec3> vertices, int n) {
    int cn = 0; // the  crossing number counter

    // loop through all edges of the polygon
    for (int i = 0; i < n; i++) {
        // edge from V[i]  to V[i+1]
        if (((vertices[i].y <= P.y) && (vertices[i + 1].y > P.y)) // an upward crossing
            || ((vertices[i].y > P.y) && (vertices[i + 1].y <= P.y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float) (P.y - vertices[i].y) / (vertices[i + 1].y - vertices[i].y);
            if (P.x < vertices[i].x + vt * (vertices[i + 1].x - vertices[i].x)) // P.x < intersect
                ++cn;                                                           // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn & 1); // 0 if even (out), and 1 if  odd (in)
}

bool leftMouseDown(int button, int state) {
    return button == MouseButton::Left && state == MouseState::Down;
}

bool leftMouseUp(int button, int state) {
    return button == MouseButton::Left && state == MouseState::Up;
}

dvec3 lerp(dvec3 x0, dvec3 x1, float t) {
    return x0 * (1 - t) + x1 * t;
}

dvec4 lerp(dvec4 x0, dvec4 x1, float t) {
    return x0 * (1 - t) + x1 * t;
}

float lerp(float v0, float v1, float t) {
    return v0 * (1 - t) + v1 * t;
}

float clamp(float v0, float v1, float v) {
    if (v < v0) return v0;
    if (v > v1) return v1;
    return v;
}

float round(float v0, float v1, float v) {
    float distV0 = abs(v - v0);
    float distV1 = abs(v - v1);
    if (distV0 < distV1) return v0;
    if (distV1 > distV0) return v1;
    return v1;

}

std::vector<dvec3> generateCircle(dvec3 center, dvec3 scale, float sides) {
    float ang, x1, y1;
    float inc = PI_2 / sides;
    std::vector<dvec3> vertices;
    for (ang = 0; ang < PI_2; ang += inc) {
        float x = (cos(ang) * scale.x);
        float y = (sin(ang) * scale.y);
        vertices.push_back({center.x + x, center.y + y, center.z});
    }
    vertices.push_back(vertices[0]);
    return vertices;
}

bool isPointInsideCircle(dvec2 point, dvec2 center, float radius) {
    return std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2) <= std::pow(radius, 2);
}

dvec3 HSVtoRGB(dvec3 hsv) {

    double r = 0, g = 0, b = 0;

    if (hsv.y == 0) {
        r = hsv.z;
        g = hsv.z;
        b = hsv.z;
    } else {
        int i;
        double f, p, q, t;

        if (hsv.x == 360)
            hsv.x = 0;
        else
            hsv.x = hsv.x / 60;

        i = (int) hsv.x;
        f = hsv.x - i;

        p = hsv.z * (1.0 - hsv.x);
        q = hsv.z * (1.0 - (hsv.x * f));
        t = hsv.z * (1.0 - (hsv.x * (1.0 - f)));

        switch (i) {
            case 0:
                r = hsv.z;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = hsv.z;
                b = p;
                break;

            case 2:
                r = p;
                g = hsv.z;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = hsv.z;
                break;

            case 4:
                r = t;
                g = p;
                b = hsv.z;
                break;

            default:
                r = hsv.z;
                g = p;
                b = q;
                break;
        }

    }

    return dvec3(r, g, b);
}

dvec3 RandomColorGenerator(float saturation, float brightness) {
    double rand = (std::rand() % 1000) / 1000.0;
    rand = std::min(360.0, rand * 360);
    return HSVtoRGB(dvec3(rand, saturation, brightness));
}

dvec2 getMaximumAbsValue(std::vector<dvec2> values) {
    dvec2 max = dvec2(std::abs(values[0].x), std::abs(values[0].y));
    for (int i = 0; i < values.size(); ++i) {
        dvec2 cur = values[i];
        if (std::abs(cur.x) > max.x) max.x = std::abs(cur.x);
        if (std::abs(cur.y) > max.y) max.y = std::abs(cur.y);
    }
    return max;
}

dvec2 getMaximumValue(std::vector<dvec2> values) {
    dvec2 max = dvec2(values[0].x, values[0].y);
    for (int i = 0; i < values.size(); ++i) {
        dvec2 cur = values[i];
        if (cur.x > max.x) max.x = cur.x;
        if (cur.y > max.y) max.y = cur.y;
    }
    return max;
}

dvec2 getMinimumValue(std::vector<dvec2> values) {
    dvec2 min = dvec2(values[0].x, values[0].y);
    for (int i = 0; i < values.size(); ++i) {
        dvec2 cur = values[i];
        if (cur.x < min.x) min.x = cur.x;
        if (cur.y < min.y) min.y = cur.y;
    }
    return min;
}

dvec2 rotatePoint2D(dvec2 point, float angle) {
    dvec2 rotatedPoint;
    rotatedPoint.x = std::cos(angle) * point.x - std::sin(angle) * point.y;
    rotatedPoint.y = std::sin(angle) * point.x + std::cos(angle) * point.y;
    return rotatedPoint;

}