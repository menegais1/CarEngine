//
// Created by menegais1 on 25/07/2020.
//

#include "OpenEndedCylinder.h"
#include "../Base/3D/Transform.h"
#include "ModelLoader.h"
#include "../Bitmap/Bitmap.h"
#include "../Rendering/Renderer.h"
#include "../FileLoader.h"


OpenEndedCylinder::OpenEndedCylinder(Transform transform, int sides) : Object3D(transform) {
    ObjectInfo info = ModelLoader::loadObj(FileLoader::getPath("simplified_open_cylinder.obj"));
    vertices = info.vertices;
    faces = info.faces;
    normals = info.normals;
    uvs = info.uv;
    albedo = Renderer::getInstance()->metal_albedo;
    specular = Renderer::getInstance()->metal_specular;
}

