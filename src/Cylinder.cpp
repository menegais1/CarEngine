//
// Created by menegais1 on 12/07/2020.
//

#include <Canvas/gl_canvas2d.h>
#include <Camera/Camera.h>
#include "Cylinder.h"
#include "Utilities.h"

Cylinder::Cylinder(dvec3 center, float radius, float height) : radius(radius), height(height) {
    float step = 2 * PI / 30.0;

    double z = -1 / 2.0;
    vertices.push_back(dvec3(0, 0, z));
    for (float t = 0; t < PI * 2; t += step) {
        double x = cos(t);
        double y = sin(t);
        vertices.push_back(dvec3(x, y, z));
    }
    for (int i = 1; i < vertices.size() - 1; ++i) {
        triangles.push_back(0);
        triangles.push_back(i);
        triangles.push_back(i + 1);
    }

    z = 1 / 2.0;
    vertices.push_back(dvec3(0, 0, z));
    int centerUp = vertices.size() - 1;
    for (float t = 0; t < PI * 2; t += step) {
        double x = cos(t);
        double y = sin(t);
        vertices.push_back(dvec3(x, y, z));
    }
    for (int i = centerUp + 1; i < vertices.size() - 1; ++i) {
        triangles.push_back(centerUp);
        triangles.push_back(i);
        triangles.push_back(i + 1);
    }

    for (int i = 1; i < (vertices.size() / 2) - 1; i++) {
        triangles.push_back(i);
        triangles.push_back(i + centerUp);
        triangles.push_back(i + centerUp + 1);
        triangles.push_back(i + 1);
        triangles.push_back(i);
        triangles.push_back(i + centerUp + 1);
    }
    rescale(dvec3(radius, radius, height));
    setCenter(center);
}

void Cylinder::render() {
    std::vector<dvec3> projVertices = vertices;
    rotateZ(1 * PI / 180);
    for (int i = 0; i < projVertices.size(); ++i) {
        projVertices[i] = Camera::getInstance()->convertNDCToViewport(
                Camera::getInstance()->clipCoordinates(
                        Camera::getInstance()->convertViewToProjection(Camera::getInstance()->removeBackCameraVertex(
                                Camera::getInstance()->convertWorldToView(
                                        (Model * projVertices[i].toVector4(1)).toVector3())))));
    }
    CV::color(0, 0, 0, 1);
    for (int i = 0; i < triangles.size() - 2; i += 3) {
        CV::line(projVertices[triangles[i]], projVertices[triangles[i + 1]]);
        CV::line(projVertices[triangles[i + 1]], projVertices[triangles[i + 2]]);
        CV::line(projVertices[triangles[i + 2]], projVertices[triangles[i]]);
    }
}


