//
// Created by menegais1 on 12/07/2020.
//

#include "../Canvas/gl_canvas2d.h"
#include "CameraMovement.h"
#include "../Utilities.h"

void CameraMovement::keyboard(int key) {
    double moveSpeed = 0.1;

    if (key == 'w') {
        camera->generateViewMatrix(camera->center + camera->forward * moveSpeed,
                                   camera->at + camera->forward * moveSpeed, dvec3(0,1,0));
    } else if (key == 's') {
        camera->generateViewMatrix(camera->center + camera->forward * -moveSpeed,
                                   camera->at + camera->forward * -moveSpeed, dvec3(0,1,0));
    } else if (key == 'd') {
        camera->generateViewMatrix(camera->center + camera->right * moveSpeed, camera->at + camera->right * moveSpeed,
                                   dvec3(0,1,0));
    } else if (key == 'a') {
        camera->generateViewMatrix(camera->center + camera->right * -moveSpeed, camera->at + camera->right * -moveSpeed,
                                   dvec3(0,1,0));
    } else if (key == 'q') {
        camera->generateViewMatrix(camera->center + dvec3(0,1,0) * moveSpeed, camera->at + dvec3(0,1,0) * moveSpeed,
                                   dvec3(0,1,0));
    } else if (key == 'e') {
        camera->generateViewMatrix(camera->center + dvec3(0,1,0) * -moveSpeed, camera->at + dvec3(0,1,0)* -moveSpeed,
                                   dvec3(0,1,0));
    }
}

void CameraMovement::mouse(int button, int state, int wheel, int direction, int x, int y) {
    if (leftMouseDown(button, state)) {
        isDragging = true;
    } else if (leftMouseUp(button, state)) {
        isDragging = false;
    }
    if (isDragging) {

        int xDelta = x - lastMousePosition.x;
        int yDelta = y - lastMousePosition.y;

        angle.x += yDelta;

        if (angle.x > 90) {
            angle.x = 90;
            yDelta = 0;
        } else if (angle.x < -90) {
            angle.x = -90;
            yDelta = 0;
        }
        auto RY = dMatrix::rotateY(-xDelta * PI / 180.0);
        auto RX = dMatrix::rotateX((camera->forward.z < 0 ? yDelta : -yDelta) * PI / 180.0);
        auto R = RX * RY;
        dvec3 rotatedEye = (R * (camera->at - camera->center).toVector4(1)).toVector3() + camera->center;
        dvec3 rotatedUp = (R * camera->up.toVector4(1)).toVector3();
        camera->generateViewMatrix(camera->center, rotatedEye, dvec3(0, 1, 0));
    }
    lastMousePosition = dvec2(x, y);
}

CameraMovement::CameraMovement(Camera *camera) : camera(camera), angle(0, 0) {}


void CameraMovement::render() {
    dvec3 up = dvec3(0, 10, 0);
    dvec3 right = dvec3(10, 0, 0);
    dvec3 forward = dvec3(0, 0, 10);
    dvec3 zero = dvec3(0, 0, 0);

    up = camera->convertModelToViewport(up, dMatrix::identity(4));
    right = camera->convertModelToViewport(right, dMatrix::identity(4));
    forward = camera->convertModelToViewport(forward, dMatrix::identity(4));
    zero = camera->convertModelToViewport(zero, dMatrix::identity(4));
    CV::color(1,0,0,1);
    CV::line(zero, up);
    CV::color(0,1,0,1);
    CV::line(zero, right);
    CV::color(0,0,1,1);
    CV::line(zero, forward);
}