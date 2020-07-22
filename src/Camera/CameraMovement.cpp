//
// Created by menegais1 on 12/07/2020.
//

#include <sstream>
#include "../Rendering/Canvas/gl_canvas2d.h"
#include "CameraMovement.h"
#include "../Utilities.h"
#include "../Rendering/Renderer.h"
#include "../Managers/GlobalManager.h"

void CameraMovement::keyboard(int key) {
    double moveSpeed = 0.1;

    if (key == 'o') {
        camera->cameraType = CameraType::Orthographic;
        camera->generateOrtographicProjectionMatrix(camera->getWidth(), camera->getHeight(), camera->getAspectRatio(), camera->getNear(), camera->getFar());
    }

    if (key == 'p') {
        camera->cameraType = CameraType::Perspective;
        Camera::getInstance()->generateProjectionMatrix(camera->getFov(), camera->getAspectRatio(), camera->getNear(), camera->getFar());
    }

    if (key == 'm') {
        if (Renderer::getInstance()->isActive) {
            CV::setClearColor(dvec4(1, 1, 1, 1));
        } else {
            CV::setClearColor(dvec4(0, 0, 0, 0));
        }
        Renderer::getInstance()->isActive = !Renderer::getInstance()->isActive;
    }

    if (Renderer::getInstance()->isActive) {
        if (key == 'j') {
            Renderer::getInstance()->shaderType = ShaderType::Flat;
        }
        if (key == 'k') {
            Renderer::getInstance()->shaderType = ShaderType::Goraud;
        }
        if (key == 'l') {
            Renderer::getInstance()->shaderType = ShaderType::Phong;
        }
    }

    if (key == 'w' && camera->cameraType == CameraType::Perspective) {
        camera->generateViewMatrix(camera->center + camera->forward * moveSpeed,
                                   camera->at + camera->forward * moveSpeed, dvec3(0, 1, 0));
    } else if (key == 's' && camera->cameraType == CameraType::Perspective) {
        camera->generateViewMatrix(camera->center + camera->forward * -moveSpeed,
                                   camera->at + camera->forward * -moveSpeed, dvec3(0, 1, 0));
    } else if (key == 'd') {
        camera->generateViewMatrix(camera->center + camera->right * moveSpeed, camera->at + camera->right * moveSpeed,
                                   dvec3(0, 1, 0));
    } else if (key == 'a') {
        camera->generateViewMatrix(camera->center + camera->right * -moveSpeed, camera->at + camera->right * -moveSpeed,
                                   dvec3(0, 1, 0));
    } else if (key == 'q') {
        camera->generateViewMatrix(camera->center + dvec3(0, 1, 0) * moveSpeed, camera->at + dvec3(0, 1, 0) * moveSpeed,
                                   dvec3(0, 1, 0));
    } else if (key == 'e') {
        camera->generateViewMatrix(camera->center + dvec3(0, 1, 0) * -moveSpeed, camera->at + dvec3(0, 1, 0) * -moveSpeed,
                                   dvec3(0, 1, 0));
    }
}

void CameraMovement::mouse(int button, int state, int wheel, int direction, int x, int y) {
    if (leftMouseDown(button, state)) {
        isDragging = true;
    } else if (leftMouseUp(button, state)) {
        isDragging = false;
    }
    if (isDragging && camera->cameraType == CameraType::Perspective) {

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

CameraMovement::CameraMovement(Camera *camera) : camera(camera), angle(0, 0) {
    setObjectOrder(10000);
}


void CameraMovement::render() {
    dvec3 up = dvec3(0, 10, 0);
    dvec3 right = dvec3(10, 0, 0);
    dvec3 forward = dvec3(0, 0, 10);
    dvec3 zero = dvec3(0, 0, 0);

    up = camera->convertModelToViewport(up, dMatrix::identity(4));
    right = camera->convertModelToViewport(right, dMatrix::identity(4));
    forward = camera->convertModelToViewport(forward, dMatrix::identity(4));
    zero = camera->convertModelToViewport(zero, dMatrix::identity(4));
    CV::color(1, 0, 0, 1);
    CV::line(zero, up);
    CV::color(0, 1, 0, 1);
    CV::line(zero, right);
    CV::color(0, 0, 1, 1);
    CV::line(zero, forward);

    CV::color(0, 0, 0, 1);
    std::stringstream stream;
    stream << GlobalManager::getInstance()->fps;
    CV::text(dvec2(GlobalManager::getInstance()->screenWidth - 60, GlobalManager::getInstance()->screenHeight - 20), stream.str().c_str());
    stream.str("");
    stream << GlobalManager::getInstance()->deltaTime;
    CV::text(dvec2(GlobalManager::getInstance()->screenWidth - 60, GlobalManager::getInstance()->screenHeight - 40), stream.str().c_str());


}
