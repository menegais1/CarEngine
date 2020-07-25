//
// Created by menegais1 on 25/07/2020.
//

#include "OpenEndedCylinder.h"
#include "../Base/3D/Transform.h"
#include "ModelLoader.h"


OpenEndedCylinder::OpenEndedCylinder(Transform transform, int sides) : Object3D(transform) {
    ObjectInfo info = ModelLoader::loadObj("../open_cylinder.obj");
    vertices = info.vertices;
    triangles = info.triangles;

    for (int j = 0; j < vertices.size(); ++j) {
        normals.push_back(dvec3(0, 0, 0));
    }
    for (int i = 0; i < triangles.size() - 2; i += 3) {
        dvec3 v0 = vertices[triangles[i]];
        dvec3 v1 = vertices[triangles[i + 1]];
        dvec3 v2 = vertices[triangles[i + 2]];

        dvec3 normal = (v1 - v0).cross(v2 - v0).unit();
        setNormal(triangles[i], normal);
        setNormal(triangles[i + 1], normal);
        setNormal(triangles[i + 2], normal);
    }
}

