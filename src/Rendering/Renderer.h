//
// Created by menegais1 on 14/07/2020.
//

#ifndef CARENGINE_RENDERER_H
#define CARENGINE_RENDERER_H


#include "../Vectors/Vector3.h"
#include "../Base/CanvasObject.h"
#include "IShader.h"
#include "../Bitmap/Bitmap.h"

class Renderer : CanvasObject {
public:
    dvec3 *frameBuffer;
    float *depthBuffer;
    bool isActive;
    int width;
    int height;
    ShaderType shaderType;
    Bitmap *metal_albedo = nullptr;
    Bitmap *metal_specular = nullptr;

    void triangle(Vertex v1, Vertex v2, Vertex v3, IShader *shader);

    dvec3 barycentricCoordinates(dvec3 v1, dvec3 v2, dvec3 v3, dvec3 p);

    dvec2 getMax(dvec2 v1, dvec2 v2, dvec2 v3);

    dvec2 getMin(dvec2 v1, dvec2 v2, dvec2 v3);

    static Renderer *getInstance();

    void setScreenProportions(int width, int height);

    Renderer(int width, int height);

private:
    void _triangle(Vertex v1, Vertex v2, Vertex v3, IShader *shader);

    void render() override;

    Vertex interpolateVertex(Vertex v0, Vertex v1, Vertex v2, dvec3 barycentric);

    Vertex vertexLerp(Vertex x0, Vertex x1, float t);

    Vertex convertVertexFromClipToViewport(Vertex v);

};


#endif //CARENGINE_RENDERER_H
