//
// Created by menegais1 on 12/07/2020.
//

#include "../../Camera/Camera.h"
#include "../../Rendering/Canvas/gl_canvas2d.h"
#include "Object3D.h"
#include "../../Utilities.h"
#include "../../Rendering/Renderer.h"
#include "../../Rendering/FlatShader.h"

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
    if (triangles.size() == 0) return;
    if (std::abs(transform.rotation.x) >= 360) transform.rotation.x = (int) transform.rotation.x % 360;
    if (std::abs(transform.rotation.y) >= 360) transform.rotation.y = (int) transform.rotation.y % 360;
    if (std::abs(transform.rotation.z) >= 360) transform.rotation.z = (int) transform.rotation.z % 360;


    auto S = dMatrix::scale(transform.scale);
    auto T = dMatrix::translate(transform.position);
    auto Rx = dMatrix::rotateX(transform.rotation.x * PI / 180.0);
    auto Ry = dMatrix::rotateY(transform.rotation.y * PI / 180.0);
    auto Rz = dMatrix::rotateZ(transform.rotation.z * PI / 180.0);
    Model = T * Rz * Ry * Rx * S;

    CV::color(1, 1, 1, 1);
    FlatShader *flatShader = new FlatShader();
    flatShader->IN_Color = dvec3(0.8, 0.8, 0.8);
    flatShader->IN_LightPosition = dvec3(0, 3, 0);
    flatShader->IN_Model = Model;
    flatShader->IN_ModelInverse = Model.invert();
    int cont = 0;
    for (int i = 0; i < triangles.size() - 2; i += 3) {
        cont++;
        dvec3 v0 = vertices[triangles[i]];
        dvec3 v1 = vertices[triangles[i + 1]];
        dvec3 v2 = vertices[triangles[i + 2]];
        dvec3 normal = (v1 - v0).cross(v2 - v0);
        dvec3 center = (v0 + v1 + v2) / 3.0;
        flatShader->IN_Normal = normal;
        v0 = flatShader->vertexShader(v0);
        v1 = flatShader->vertexShader(v1);
        v2 = flatShader->vertexShader(v2);
        Renderer::getInstance()->triangle(v0, v1, v2, flatShader);
//        center = (v0 + v1 + v2) / 3.0;
//        normal = Camera::getInstance()->convertModelToViewport(center + normal.unit() * 1, Model);

//        if (cont < 10) {
//            CV::color(0, 1, 0, 1);
//            CV::line(center, normal);
//            CV::color(0, 0, 1, 1);
//            CV::line(v0, v1);
//            CV::line(v1, v2);
//            CV::line(v2, v0);
//        } else{
//            CV::color(1, 0, 0, 1);
//            CV::line(center, normal);
//            CV::color(1, 1, 1, 1);
//            CV::line(v0, v1);
//            CV::line(v1, v2);
//            CV::line(v2, v0);
//        }


    }
}
