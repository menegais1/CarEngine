//
// Created by menegais1 on 12/07/2020.
//

#include <Camera/Camera.h>
#include <Canvas/gl_canvas2d.h>
#include "Object3D.h"
#include "../Utilities.h"

Object3D::Object3D(Transform transform) {
    Model = dMatrix::identity(4);
    this->transform = transform;
}

void Object3D::setCenter(dvec3 center) {
    Model.setCol(center.toVector4(1), 3);
    this->transform.position = center;
}

void Object3D::computeCenter() {
    this->transform.position = dvec3(0, 0, 0);
    for (int i = 0; i < vertices.size(); ++i) {
        this->transform.position.x += vertices[i].x;
        this->transform.position.y += vertices[i].y;
        this->transform.position.z += vertices[i].z;
    }
    this->transform.position = this->transform.position / vertices.size();
    setCenter(this->transform.position);

}

void Object3D::render() {
    auto S = dMatrix::scale(transform.scale);
    auto T = dMatrix::translate(transform.position);
    auto Rx = dMatrix::rotateX(transform.rotation.x * PI / 180.0);
    auto Ry = dMatrix::rotateY(transform.rotation.y * PI / 180.0);
    auto Rz = dMatrix::rotateZ(transform.rotation.z * PI / 180.0);
    Model = T * Rz * Ry * Rx * S;

    CV::color(0, 0, 0, 1);
    for (int i = 0; i < triangles.size() - 2; i += 3) {
        dvec3 v0 = Camera::getInstance()->convertModelToViewport(vertices[triangles[i]], Model);
        dvec3 v1 = Camera::getInstance()->convertModelToViewport(vertices[triangles[i + 1]], Model);
        dvec3 v2 = Camera::getInstance()->convertModelToViewport(vertices[triangles[i + 2]], Model);
        CV::line(v0, v1);
        CV::line(v1, v2);
        CV::line(v2, v0);
    }
}
