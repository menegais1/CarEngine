//
// Created by menegais1 on 12/07/2020.
//

#include "../Rendering/Canvas/gl_canvas2d.h"
#include "../Camera/Camera.h"
#include "Cylinder.h"
#include "../Utilities.h"

Cylinder::Cylinder(Transform transform, int sides) : Object3D(transform) {
    float step = 2 * PI / sides;

    double z = -1 / 2.0;
    vertices.push_back(dvec3(0, 0, z));
    for (float t = 0; t < PI * 2; t += step) {
        double x = cos(t);
        double y = sin(t);
        vertices.push_back(dvec3(x, y, z));
        normals.push_back(dvec3(0, 0, 0));
    }
    for (int i = 1; i < vertices.size() - 1; ++i) {
        triangles.push_back(0);
        triangles.push_back(i + 1);
        triangles.push_back(i);

        dvec3 normal = calculateNormal(0, i + 1, i);
        setNormal(0, normal);
        setNormal(i + 1, normal);
        setNormal(i, normal);
    }

    z = 1 / 2.0;
    vertices.push_back(dvec3(0, 0, z));
    normals.push_back(dvec3(0, 0, 0));
    int centerUp = vertices.size() - 1;
    for (float t = 0; t < PI * 2; t += step) {
        double x = cos(t);
        double y = sin(t);
        vertices.push_back(dvec3(x, y, z));
        normals.push_back(dvec3(0, 0, 0));
    }
    for (int i = centerUp + 1; i < vertices.size() - 1; ++i) {
        triangles.push_back(centerUp);
        triangles.push_back(i);
        triangles.push_back(i + 1);
        dvec3 normal = calculateNormal(centerUp, i, i + 1);
        setNormal(centerUp, normal);
        setNormal(i, normal);
        setNormal(i + 1, normal);
    }

    for (int i = 1; i < (vertices.size() / 2) - 1; i++) {
        triangles.push_back(i);
        triangles.push_back(i + centerUp + 1);
        triangles.push_back(i + centerUp);
        dvec3 normal = calculateNormal(i, i + centerUp + 1, i + centerUp);
        setNormal(i, normal);
        setNormal(i + centerUp + 1, normal);
        setNormal(i + centerUp, normal);
        triangles.push_back(i + 1);
        triangles.push_back(i + centerUp + 1);
        triangles.push_back(i);
        normal = calculateNormal(i + 1, i + centerUp + 1, i);
        setNormal(i + 1, normal);
        setNormal(i + centerUp + 1, normal);
        setNormal(i, normal);

    }
}



