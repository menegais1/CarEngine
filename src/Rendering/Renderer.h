//
// Created by menegais1 on 14/07/2020.
//

#ifndef CARENGINE_RENDERER_H
#define CARENGINE_RENDERER_H


#include "../Vectors/Vector3.h"
#include "../Base/CanvasObject.h"
#include "IShader.h"

class Renderer : CanvasObject {
public:
    dvec3 *frameBuffer;
    float *depthBuffer;

    int *width;
    int *height;

    void triangle(Vector3<double> v1, Vector3<double> v2, Vector3<double> v3,IShader* shader);

    dvec3 barycentricCoordinates(dvec3 v1, dvec3 v2, dvec3 v3, dvec3 p);

    dvec2 getMax(dvec2 v1, dvec2 v2, dvec2 v3);

    dvec2 getMin(dvec2 v1, dvec2 v2, dvec2 v3);

    static Renderer *getInstance();

public:
    Renderer(int *width, int *height);

private:
    void render() override;
};


#endif //CARENGINE_RENDERER_H
