//
// Created by menegais1 on 01/07/2020.
//

#include "Camera.h"
#include <cmath>

dMatrix Camera::generateViewMatrix(dvec3 center, dvec3 eye, dvec3 up) {
    this->center = center;
    this->eye = eye;
    this->up = up;
    dvec3 forward = eye.unit();
    dvec3 right = up.cross(forward).unit();
    up = forward.cross(right).unit();

    dMatrix T(4, 4);
    T.m = {{1, 0, 0, -center.x},
           {0, 1, 0, -center.y},
           {0, 0, 1, -center.z},
           {0, 0, 0, 1}};
    dMatrix R = dMatrix::identity(4);

    R.setRow(right.toVector4(0), 0);
    R.setRow(up.toVector4(0), 1);
    R.setRow(forward.toVector4(0), 2);
    View = R * T;
    return View;
}

dMatrix Camera::generateProjectionMatrix(float fov,float aspectRatio, float near, float far) {
    dMatrix P = dMatrix::identity(4);
    P.m = {{1.0 / (std::tan(fov / 2.0) * aspectRatio), 0,                     0,                           0},
           {0,                     1.0 / std::tan(fov / 2.0), 0,                           0},
           {0,                     0,                     (near + far) / (far - near), (2 * near * far) / (far - near)},
           {0,                     0,                     -1,                          0}};
    Projection = P;
    return Projection;
}

void Camera::setViewport(int width, int height, int x, int y) {
    this->Vx = x;
    this->Vy = y;
    this->Vheight = height;
    this->Vwidth = width;
}

dvec3 Camera::convertNDCToViewport(dvec3 ndc) {
    return dvec3(((ndc.x + 1) * Vwidth / 2.0) + Vx, ((ndc.y + 1) * Vheight / 2.0) + Vy, ndc.z);
}

dvec3 Camera::convertToProjectionSpace(dvec3 vertex) {
    auto projectedPoint = Projection * View * vertex.toVector4(1);
    return dvec3(projectedPoint[0][0] / projectedPoint[3][0], projectedPoint[1][0] / projectedPoint[3][0],
                 projectedPoint[2][0] / projectedPoint[3][0]);
}


Camera *Camera::getInstance() {
    static Camera *c = new Camera();
    return c;
}

Camera::Camera() {

}


