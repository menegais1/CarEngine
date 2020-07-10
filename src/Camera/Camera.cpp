//
// Created by menegais1 on 01/07/2020.
//

#include "Camera.h"

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

dMatrix Camera::generateProjectionMatrix(float planeDistance) {
    dMatrix P = dMatrix::identity(4);
    P.setRow(dvec4(0, 0, -(1 / planeDistance), 0), 3);
    Projection = P;
    return Projection;
}

dMatrix Camera::generateViewPortMatrix(int width, int height, int x, int y) {
    dMatrix VP = dMatrix::identity(4);
    VP.m = {{(width) / (double) x, 0,                     0, (double) width},
            {0,                    (height) / (double) y, 0, (double) height},
            {0,                    0,                     0, 0},
            {0,                    0,                     0, 1}};

    Viewport = VP;
    return Viewport;
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

dvec3 Camera::projectionToViewport(dvec3 vertex) {
    auto viewportPoint = Viewport * vertex.toVector4(1);
    return dvec3(viewportPoint[0][0], viewportPoint[1][0],
                 viewportPoint[2][0]);
}

