//
// Created by menegais1 on 01/07/2020.
//

#include <Camera/Camera.h>
#include <Canvas/gl_canvas2d.h>
#include "Cube.h"

Cube::Cube(dvec3 center, dvec3 size) {
    vertices = std::vector<dvec3>(8);
    vertices[0] = center + dvec3(-size.x, -size.y, size.z) / 2.0;
    vertices[1] = center + dvec3(size.x, -size.y, size.z) / 2.0;
    vertices[2] = center + dvec3(size.x, +size.y, size.z) / 2.0;
    vertices[3] = center + dvec3(-size.x, +size.y, size.z) / 2.0;
    vertices[4] = center + dvec3(-size.x, -size.y, -size.z) / 2.0;
    vertices[5] = center + dvec3(size.x, -size.y, -size.z) / 2.0;
    vertices[6] = center + dvec3(size.x, +size.y, -size.z) / 2.0;
    vertices[7] = center + dvec3(-size.x, +size.y, -size.z) / 2.0;
}

void Cube::mouse(int button, int state, int wheel, int direction, int x, int y) {
    CanvasObject::mouse(button, state, wheel, direction, x, y);
}

void Cube::render() {
    std::vector<dvec3> projVertices = vertices;
    for (int i = 0; i < projVertices.size(); ++i) {
        projVertices[i] = Camera::getInstance()->projectionToViewport(
                Camera::getInstance()->convertToProjectionSpace(projVertices[i]));
        //projVertices[i].print();
    }
    CV::color(0, 0, 0, 1);
    for (int j = 0; j < projVertices.size() / 2 - 1; ++j) {
        CV::line(projVertices[j], projVertices[j + 1]);
        CV::line(projVertices[j], projVertices[j + 4]);
        CV::line(projVertices[j + 4], projVertices[j + 5]);
    }
    CV::line(projVertices[3], projVertices[0]);
    CV::line(projVertices[3], projVertices[7]);
    CV::line(projVertices[7], projVertices[4]);
}

void Cube::keyboard(int key) {
    dvec3 translation = dvec3(0, 0, 0);
    if (key == 'w') {
        translation.z = 2;
    } else if (key == 's') {
        translation.z = -2;
    } else if (key == 'd') {
        translation.x = 2;
    } else if (key == 'a') {
        translation.x = -2;
    }
}

void Cube::keyboardUp(int key) {
    CanvasObject::keyboardUp(key);
}

void Cube::setObjectOrder(int zIndex) {
    CanvasObject::setObjectOrder(zIndex);
}

Cube::~Cube() {

}

void Cube::setActive(bool isActive) {
    CanvasObject::setActive(isActive);
}

bool Cube::pointIntersectsObject(dvec3 point) {
    return false;
}

void Cube::translate(dvec3 dvec31) {

}

void Cube::rotate(float d, dvec3 dvec31) {

}

void Cube::rescale(dvec3 dvec31, dvec3 dvec32) {

}

