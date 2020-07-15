//
// Created by menegais1 on 01/07/2020.
//

#include "Camera.h"
#include <cmath>

dMatrix Camera::generateViewMatrix(dvec3 eye, dvec3 at, dvec3 up) {
    dvec3 forward = (eye - at).unit();
    dvec3 right = up.cross(forward).unit();
    up = forward.cross(right).unit();

    dMatrix T(4, 4);
    T.m = {{1, 0, 0, -eye.x},
           {0, 1, 0, -eye.y},
           {0, 0, 1, -eye.z},
           {0, 0, 0, 1}};
    dMatrix R = dMatrix::identity(4);

    R.setRow(right.toVector4(0), 0);
    R.setRow(up.toVector4(0), 1);
    R.setRow(forward.toVector4(0), 2);
    View = R * T;
    this->right = right;
    this->forward = -forward;
    this->up = up;
    this->center = eye;
    this->at = at;
    return View;
}

dMatrix Camera::generateProjectionMatrix(float fov, float aspectRatio, float near, float far) {
    dMatrix P = dMatrix::identity(4);
    P.m = {{1.0 / (std::tan(fov / 2.0) * aspectRatio), 0,                         0,                                   0},
           {0,                                         1.0 / std::tan(fov / 2.0), 0,                                   0},
           {0,                                         0,                         (near + far) / (float) (far - near), (2 * near * far) / (float) (far - near)},
           {0,                                         0,                         -1,                                  0}};
    Projection = P;

    this->_fov = fov;
    this->_aspectRatio = aspectRatio;
    this->_near = near;
    this->_far = far;
    this->_height = std::tan(fov / 2.0) * (far + near) / 2;;
    this->_width =_height * aspectRatio;
    return Projection;
}

dMatrix Camera::generateOrtographicProjectionMatrix(float width, float height, float aspectRatio, float near, float far) {
    dMatrix P = dMatrix::identity(4);
    P.m = {{1.0 / width * aspectRatio, 0,            0, 0},
           {0,                         1.0 / height, 0, 0},
           {0,                         0,            (near + far) / (float) (far - near), (2 * near * far) / (float) (far - near)},
           {0,                         0,            0, 1}};
    Projection = P;
    this->_aspectRatio = aspectRatio;
    this->_width = width;
    this->_height = height;
    this->_near = near;
    this->_far = far;
    return Projection;
}

void Camera::setViewport(int width, int height, int x, int y) {
    this->Vx = x;
    this->Vy = y;
    this->Vheight = height;
    this->Vwidth = width;
}

dvec3 Camera::convertNDCToViewport(dvec3 ndc) {
    if(ndc.x > 1 || ndc.x < -1 || ndc.y < -1 || ndc.y > 1) return dvec3(NAN,NAN,NAN);
    return dvec3(((ndc.x + 1) * Vwidth / 2.0) + Vx, ((ndc.y + 1) * Vheight / 2.0) + Vy, ndc.z);
}

dvec3 Camera::clipCoordinates(dvec3 vertex) {
    return vertex;
}

dvec3 Camera::removeBackCameraVertex(dvec3 vertex) {
    if (vertex.z > 0) return dvec3(NAN, NAN, NAN);
    return vertex;
}

dvec3 Camera::convertWorldToView(dvec3 vertex) {
    auto projectedPoint = View * vertex.toVector4(1);
    return projectedPoint.toVector3();
}

dvec3 Camera::convertModelToViewport(dvec3 vertex, dMatrix Model) {
    return convertNDCToViewport(convertViewToProjection(
            removeBackCameraVertex(convertWorldToView((Model * vertex.toVector4(1)).toVector3()))));
}

dvec3 Camera::convertViewToProjection(dvec3 vertex) {
    auto projectedPoint = Projection * vertex.toVector4(1);
    return dvec3(projectedPoint[0][0] / projectedPoint[3][0], projectedPoint[1][0] / projectedPoint[3][0],
                 projectedPoint[2][0] / projectedPoint[3][0]);
}


Camera *Camera::getInstance() {
    static Camera *c = new Camera();
    return c;
}

Camera::Camera() {
    cameraType = CameraType::Perspective;
}

float Camera::getNear() const {
    return _near;
}

float Camera::getFar() const {
    return _far;
}

float Camera::getFov() const {
    return _fov;
}

float Camera::getAspectRatio() const {
    return _aspectRatio;
}

float Camera::getWidth() const {
    return _width;
}

float Camera::getHeight() const {
    return _height;
}


