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
    normals = info.normals;

}

