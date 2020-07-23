//
// Created by menegais1 on 14/07/2020.
//

#include "Renderer.h"
#include "../Vectors/Vector3.h"
#include "Canvas/gl_canvas2d.h"
#include "../Managers/GlobalManager.h"
#include "../Utilities.h"
#include "IShader.h"
#include "../Camera/Camera.h"

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

Vertex Renderer::interpolateVertex(Vertex v0, Vertex v1, Vertex v2, dvec3 barycentric) {
    Vertex v;
    v.normal = v0.normal * barycentric.x + v1.normal * barycentric.y + v2.normal * barycentric.z;
    v.color = v0.color * barycentric.x + v1.color * barycentric.y + v2.color * barycentric.z;
    return v;
}

void Renderer::_triangle(Vertex v1, Vertex v2, Vertex v3, IShader *shader) {
    if (v1.pos.x == NAN || v1.pos.y == NAN || v2.pos.x == NAN || v2.pos.y == NAN || v3.pos.x == NAN || v3.pos.y == NAN) return;
    dvec2 min = getMin(v1.pos, v2.pos, v3.pos);
    dvec2 max = getMax(v1.pos, v2.pos, v3.pos);
//    if (max.x >= *width || max.x < 0 || min.x >= *width || min.x < 0 || max.y >= *height || max.y < 0 ||
//        min.y >= *height || min.y < 0)
//        return;

    for (int x = min.x; x <= max.x; x++) {
        for (int y = min.y; y < max.y; ++y) {
            if (x < 0 || x >= *width || y < 0 || y >= *height)continue;
            dvec3 p = dvec3(x, y, 0);
            dvec3 barycentric = barycentricCoordinates(v1.pos, v2.pos, v3.pos, p);
            if (barycentric.x > 1 || barycentric.x < 0 || barycentric.y > 1 ||
                barycentric.y < 0 || barycentric.z > 1 || barycentric.z < 0)
                continue;
            p.z = v1.pos.z * barycentric.x + v2.pos.z * barycentric.y + v3.pos.z * barycentric.z;
            int idx = y * (*height) + x;
            if (depthBuffer[idx] < p.z) {
                bool discard = false;
                Vertex v = interpolateVertex(v1, v2, v3, barycentric);
                v.pos = p.toVector4(1);
                dvec4 color = shader->fragmentShader(v, barycentric, discard);
                if (discard) continue;
                frameBuffer[idx] = color;
                depthBuffer[idx] = p.z;
            }
        }
    }
}

Vertex Renderer::vertexLerp(Vertex x0, Vertex x1, float t) {
    Vertex v;
    v.pos = lerp(x0.pos, x1.pos, t);
    v.normal = lerp(x0.normal, x1.normal, t);
    v.color = lerp(x0.color, x1.color, t);
}

Vertex Renderer::convertVertexFromClipToViewport(Vertex v) {
    if(abs(v.pos.w) < 0.0001){
        v.pos = dvec4(NAN,NAN,NAN,NAN);
        return v;
    }
    v.pos = Camera::getInstance()->convertClipSpaceToNDC(v.pos).toVector4(1);
    v.pos = Camera::getInstance()->convertNDCToViewport(v.pos).toVector4(1);
    return v;
}

void Renderer::triangle(Vertex v1, Vertex v2, Vertex v3, IShader *shader) {

    Vertex vertices[] = {v1, v2, v3};
    std::vector<Vertex> outVertices;
    for (int i = 0; i < 3; ++i) {
        Vertex p0 = vertices[i];
        Vertex p1 = vertices[(i + 1) % 3];
        bool p0Out, p1Out;
        float t = Camera::getInstance()->clipLineSegmentOnNear(p0.pos, p1.pos, p0Out, p1Out);
        if (p0Out && p1Out) continue;
        if (!p1Out && !p0Out) {
            if (outVertices.size() > 0 && outVertices[outVertices.size() - 1].pos != p0.pos)
                outVertices.push_back(p0);
            else if(outVertices.size() == 0)
                outVertices.push_back(p0);
            outVertices.push_back(p1);
        } else if (p0Out && !p1Out) {
            Vertex v = vertexLerp(p0, p1, t);
            outVertices.push_back(v);
            if (outVertices.size() > 0 && outVertices[0].pos != p1.pos)
                outVertices.push_back(p1);
        } else if (!p0Out && p1Out) {
            Vertex v = vertexLerp(p0, p1, t);
            if (outVertices.size() > 0 && outVertices[outVertices.size() - 1].pos != p0.pos)
                outVertices.push_back(p0);
            else if(outVertices.size() == 0)
                outVertices.push_back(p0);
            outVertices.push_back(v);
        }
    }
    if (outVertices.size() == 0) return;

    _triangle(convertVertexFromClipToViewport(outVertices[0]), convertVertexFromClipToViewport(outVertices[1]), convertVertexFromClipToViewport(outVertices[2]), shader);

    if (outVertices.size() > 3)
        _triangle(convertVertexFromClipToViewport(outVertices[2]), convertVertexFromClipToViewport(outVertices[3]), convertVertexFromClipToViewport(outVertices[0]), shader);

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
