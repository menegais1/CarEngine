//
// Created by menegais1 on 12/07/2020.
//

#include "CameraMovement.h"
#include "../Utilities.h"

void CameraMovement::keyboard(int key) {
    double moveSpeed = 0.1;

    if (key == 'w') {
        camera->generateViewMatrix(camera->center + camera->forward * moveSpeed,
                                   camera->at + camera->forward * moveSpeed, camera->up);
    } else if (key == 's') {
        camera->generateViewMatrix(camera->center + camera->forward * -moveSpeed,
                                   camera->at + camera->forward * -moveSpeed, camera->up);
    } else if (key == 'd') {
        camera->generateViewMatrix(camera->center + camera->right * moveSpeed, camera->at + camera->right * moveSpeed,
                                   camera->up);
    } else if (key == 'a') {
        camera->generateViewMatrix(camera->center + camera->right * -moveSpeed, camera->at + camera->right * -moveSpeed,
                                   camera->up);

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


