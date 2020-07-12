//
// Created by menegais1 on 12/07/2020.
//

#include "Object3D.h"
#include "../Utilities.h"

void Object3D::translate(dvec3 translationAmount) {
    Model = dMatrix::translate(translationAmount) * Model;
}

void Object3D::rotateX(float angle) {
    translate(-center);
    Model = dMatrix::rotateX(angle) * Model;
    translate(center);
}

void Object3D::rotateZ(float angle) {
    translate(-center);
    Model = dMatrix::rotateZ(angle) * Model;
    translate(center);
}

void Object3D::rotateY(float angle) {
    translate(-center);
    Model = dMatrix::rotateY(angle) * Model;
    translate(center);
}

void Object3D::rescale(dvec3 scale) {
    Model = dMatrix::scale(scale) * Model;
}

Object3D::Object3D() {
    Model = dMatrix::identity(4);
    center = dvec3(0, 0, 0);
}

void Object3D::setCenter(dvec3 center) {
    Model.setCol(center.toVector4(1), 3);
    this->center = center;
}

void Object3D::computeCenter() {
    center = dvec3(0, 0, 0);
    for (int i = 0; i < vertices.size(); ++i) {
        center.x += vertices[i].x;
        center.y += vertices[i].y;
        center.z += vertices[i].z;
    }
    center = center / vertices.size();
    setCenter(center);

}