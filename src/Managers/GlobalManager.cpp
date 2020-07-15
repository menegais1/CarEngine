
#include <vector>
#include "../Base/CanvasObject.h"
#include "GlobalManager.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include "../Camera/Camera.h"
#include "../Vectors/Vector2.h"

using namespace std::chrono;

GlobalManager::GlobalManager() {
    screenWidth = 800;
    screenHeight = 800;
}

GlobalManager *GlobalManager::getInstance() {
    static GlobalManager *instance = new GlobalManager();
    return instance;
}

void GlobalManager::keyboard(int key) {
    std::vector<CanvasObject *> callbackCaller = objects;
    for (int i = callbackCaller.size() - 1; i >= 0; i--) {
        if (!callbackCaller[i]->checkIfCanExecuteCallback())
            continue;
        callbackCaller[i]->keyboard(key);
    }

}

void GlobalManager::keyboardUp(int key) {
    std::vector<CanvasObject *> callbackCaller = objects;
    for (int i = callbackCaller.size() - 1; i >= 0; i--) {
        if (!callbackCaller[i]->checkIfCanExecuteCallback())
            continue;
        callbackCaller[i]->keyboardUp(key);
    }

}


void GlobalManager::changeObjectOrder(CanvasObject *object) {
    auto iterator = std::find(objects.begin(), objects.end(), object);
    if (iterator != objects.cend()) {
        objects.erase(iterator);
        addObjectToList(object);
    }
}


void GlobalManager::mouse(int button, int state, int wheel, int direction, int x, int y) {
    std::vector<CanvasObject *> callbackCaller = objects;
    mousePosition = dvec2(x, y);
    for (int i = callbackCaller.size() - 1; i >= 0; i--) {
        if (!callbackCaller[i]->checkIfCanExecuteCallback())
            continue;
        callbackCaller[i]->mouse(button, state, wheel, direction, x, y);
    }

}

void GlobalManager::render() {
    currentTime = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(currentTime - lastTime);
    deltaTime = time_span.count();
    time += deltaTime;
    if (time > lastFpsUpdate + fpsUpdateCycle) {
        fps = 1.0 / deltaTime;
        lastFpsUpdate = time;
    }
    std::vector<CanvasObject *> callbackCaller = objects;
    for (int i = callbackCaller.size() - 1; i >= 0; i--) {
        if (!callbackCaller[i]->checkIfCanExecuteCallback())
            continue;
        callbackCaller[i]->render();
    }
    cleanUpObjects();

    lastTime = currentTime;
}

int GlobalManager::registerObject(CanvasObject *object) {
    addObjectToList(object);
    return objectIdCounter++;
}

void GlobalManager::addObjectToList(CanvasObject *object) {
    int size = objects.size();
    if (size == 0) {
        objects.push_back(object);
    } else {
        for (int i = 0; i < size; i++) {
            if (objects[i]->getObjectOrder() <= object->getObjectOrder()) {
                objects.insert(objects.begin() + i, object);
                break;
            }
        }
        if (size == objects.size())
            objects.push_back(object);
    }
}

CanvasObject *GlobalManager::unregisterObject(CanvasObject *object) {
    auto iterator = std::find(objects.begin(), objects.end(), object);
    if (iterator != objects.cend()) {
        objects.erase(iterator);
        return object;
    }
    return nullptr;
}

CanvasObject *GlobalManager::deleteObject(CanvasObject *object) {
    object->isValid = false;
    return nullptr;
}

CanvasObject *GlobalManager::cleanUpObjects() {
    for (int i = 0; i < objects.size(); ++i) {
        if (!objects[i]->isValid) {
            auto object = objects[i];
            unregisterObject(object);
            delete object;
            i--;
        }
    }
}

void GlobalManager::reshape(int width, int height) {
    this->screenWidth = width;
    this->screenHeight = height;

    float aspectRatio = width / (float) height;
    Camera::getInstance()->setViewport(width, height, 0, 0);
    if (Camera::getInstance()->cameraType == CameraType::Orthographic) {
        Camera::getInstance()->generateOrtographicProjectionMatrix(Camera::getInstance()->getWidth(), Camera::getInstance()->getHeight(), aspectRatio, Camera::getInstance()->getNear(), Camera::getInstance()->getFar());
    } else {
        Camera::getInstance()->generateProjectionMatrix(Camera::getInstance()->getFov(), aspectRatio, Camera::getInstance()->getNear(), Camera::getInstance()->getFar());
    }
}