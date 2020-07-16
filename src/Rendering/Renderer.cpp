//
// Created by menegais1 on 14/07/2020.
//

#include "Renderer.h"
#include "../Vectors/Vector3.h"
#include "Canvas/gl_canvas2d.h"
#include "../Managers/GlobalManager.h"
#include "../Utilities.h"
#include "IShader.h"

dvec2 Renderer::getMin(dvec2 v1, dvec2 v2, dvec2 v3) {
    dvec2 min = v1;
    if (v2.x < min.x) min.x = v2.x;
    if (v3.x < min.x) min.x = v3.x;
    if (v2.y < min.y) min.y = v2.y;
    if (v3.y < min.y) min.y = v3.y;
    return min;
}

dvec2 Renderer::getMax(dvec2 v1, dvec2 v2, dvec2 v3) {
    dvec2 max = v1;
    if (v2.x > max.x)max.x = v2.x;
    if (v3.x > max.x)max.x = v3.x;
    if (v2.y > max.y)max.y = v2.y;
    if (v3.y > max.y)max.y = v3.y;
    return max;
}

//Using cramer rule to solve the system
dvec3 Renderer::barycentricCoordinates(dvec3 v1, dvec3 v2, dvec3 v3, dvec3 p) {
    dvec2 v21 = v2 - v1;
    dvec2 v31 = v3 - v1;
    dvec2 va1 = p - v1;
    float det = v21.x * v31.y - v31.x * v21.y;
    if (det == 0) return dvec3(-1, -1, -1);
    float v = (va1.x * v31.y - v31.x * va1.y) / det;
    float w = (v21.x * va1.y - va1.x * v21.y) / det;
    float u = 1.0 - v - w;
    return dvec3(u, v, w);
}

void Renderer::triangle(dvec3 v1, dvec3 v2, dvec3 v3, IShader *shader) {
    if (v1.x == NAN || v1.y == NAN || v2.x == NAN || v2.y == NAN || v3.x == NAN || v3.y == NAN) return;
    dvec2 min = getMin(v1, v2, v3);
    dvec2 max = getMax(v1, v2, v3);
    if (min.x >= *width || min.x < 0 || max.y >= *height || max.y < 0) return;
    dvec3 color = RandomColorGenerator(0.5, 0.5);
    for (int x = min.x; x <= max.x; x++) {
        for (int y = min.y; y < max.y; ++y) {
            dvec3 p = dvec3(x, y, 0);
            dvec3 barycentric = barycentricCoordinates(v1, v2, v3, p);
            if (barycentric.x > 1 || barycentric.x < 0 || barycentric.y > 1 ||
                barycentric.y < 0 || barycentric.z > 1 || barycentric.z < 0)
                continue;
            p.z = v1.z * barycentric.x + v2.z * barycentric.y + v3.z * barycentric.z;
            int idx = y * (*height) + x;
            if (depthBuffer[idx] < p.z) {
                bool discard = false;
                dvec4 color = shader->fragmentShader(barycentric, discard);
                if (discard) continue;
                frameBuffer[idx] = color;
                depthBuffer[idx] = p.z;
            }
        }
    }
}

void Renderer::render() {
    if (!isActive) return;
    for (int x = 0; x < *width; x++) {
        for (int y = 0; y < *height; ++y) {
            int idx = y * (*height) + x;
            CV::color(frameBuffer[idx]);
            CV::point(x, y);
            frameBuffer[idx] = {1, 1, 1};
            depthBuffer[idx] = -10000;
        }
    }
}

Renderer *Renderer::getInstance() {
    static Renderer *instance = new Renderer(&GlobalManager::getInstance()->screenWidth,
                                             &GlobalManager::getInstance()->screenHeight);
    return instance;
}

Renderer::Renderer(int *width, int *height) : width(width), height(height) {
    int size = *width * *height;
    frameBuffer = new dvec3[size];
    depthBuffer = new float[size];

    for (int i = 0; i < size; ++i) {
        frameBuffer[i] = dvec3(1, 1, 1);
        depthBuffer[i] = -100000;
    }

    setObjectOrder(1000);
    isActive = false;
    shaderType = ShaderType::Flat;
}
