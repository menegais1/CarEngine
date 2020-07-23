//
// Created by menegais1 on 01/07/2020.
//

#include "Camera.h"
#include <cmath>
#include "../Utilities.h"
#include "../Rendering/Canvas/gl_canvas2d.h"

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

dMatrix Camera::generateProjectionMatrix(float fov, float aspectRatio, float _near, float _far) {
    dMatrix P = dMatrix::identity(4);
    P.m = {{1.0 / (std::tan(fov / 2.0) * aspectRatio), 0,                         0,                                       0},
           {0,                                         1.0 / std::tan(fov / 2.0), 0,                                       0},
           {0,                                         0,                         (_near + _far) / (float) (_far - _near), (2 * _near * _far) / (float) (_far - _near)},
           {0,                                         0,                         -1,                                      0}};
    Projection = P;

    this->_fov = fov;
    this->_aspectRatio = aspectRatio;
    this->_near = _near;
    this->_far = _far;
    this->_height = std::tan(fov / 2.0) * (_far + _near) / 2;;
    this->_width = _height * aspectRatio;
    return Projection;
}

dMatrix Camera::generateOrtographicProjectionMatrix(float width, float height, float aspectRatio, float _near, float _far) {
    dMatrix P = dMatrix::identity(4);
    P.m = {{1.0 / width * aspectRatio, 0,            0,                                       0},
           {0,                         1.0 / height, 0,                                       0},
           {0,                         0,            (_near + _far) / (float) (_far - _near), (2 * _near * _far) / (float) (_far - _near)},
           {0,                         0,            0,                                       1}};
    Projection = P;
    this->_aspectRatio = aspectRatio;
    this->_width = width;
    this->_height = height;
    this->_near = _near;
    this->_far = _far;
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

float Camera::clipLineSegmentOnNear(dvec4 p0, dvec4 p1, bool &p0Out, bool &p1Out) {
    if (-p0.z + p0.w > 0 && -p1.z + p1.w > 0) {
        p0Out = p1Out = false;
        return 0;
    }
    if (-p0.z + p0.w < 0 && -p1.z + p1.w < 0) {
        p0Out = p1Out = true;
        return 0;
    } else if (-p0.z + p0.w < 0) {
        float t = -((p0.w - p0.z) / ((p0.z + p1.w) - (p0.w + p1.z)));
        p0Out = true;
        p1Out = false;
        return t;
    } else {
        float t = -((p0.w - p0.z) / ((p0.z + p1.w) - (p0.w + p1.z)));
        p0Out = false;
        p1Out = true;
        return t;
    }
}

dvec3 Camera::convertWorldToView(dvec3 vertex) {
    auto projectedPoint = View * vertex.toVector4(1);
    return projectedPoint.toVector3();
}

dvec4 Camera::convertViewToClipSpace(dvec3 vertex) {
    auto projectedPoint = Projection * vertex.toVector4(1);
    return projectedPoint.toVector4();
}

dvec3 Camera::convertClipSpaceToNDC(dvec4 vertex) {
    return dvec3(vertex.x / vertex.w, vertex.y / vertex.w, vertex.z / vertex.w);
}

void Camera::line(dvec3 p0, dvec3 p1) {
    dvec4 clipP0 = convertViewToClipSpace(convertWorldToView(p0));
    dvec4 clipP1 = convertViewToClipSpace(convertWorldToView(p1));
    bool p0Out = false, p1Out = false;
    float t = clipLineSegmentOnNear(clipP0, clipP1, p0Out, p1Out);
    if (p0Out && p1Out) return;
    if (!p1Out && !p0Out) {
        p0 = convertNDCToViewport(convertClipSpaceToNDC(clipP0));
        p1 = convertNDCToViewport(convertClipSpaceToNDC(clipP1));
        CV::line(p0, p1);
    } else if (p0Out && !p1Out) {
        clipP0 = lerp(clipP0, clipP1, t);
        p0 = convertNDCToViewport(convertClipSpaceToNDC(clipP0));
        p1 = convertNDCToViewport(convertClipSpaceToNDC(clipP1));
        CV::line(p0, p1);
    } else if (!p0Out && p1Out) {
        clipP1 = lerp(clipP0, clipP1, t);
        p0 = convertNDCToViewport(convertClipSpaceToNDC(clipP0));
        p1 = convertNDCToViewport(convertClipSpaceToNDC(clipP1));
        CV::line(p0, p1);

    }
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


