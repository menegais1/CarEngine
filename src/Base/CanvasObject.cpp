#include "CanvasObject.h"
#include "../Managers/GlobalManager.h"
#include "../Utilities.h"
#include <iostream>
#include "../Vectors/Vector3.h"

void CanvasObject::keyboard(int key) {
}

void CanvasObject::keyboardUp(int key) {
}

void CanvasObject::mouse(int button, int state, int wheel, int direction, int x, int y) {
}

void CanvasObject::render() {
}

void CanvasObject::setActive(bool isActive) {
    lastActiveState = this->isActive;
    this->isActive = isActive;
}

bool CanvasObject::getActive() {
    return this->isActive;
}

bool CanvasObject::checkIfCanExecuteCallback() {
    if (!isValid) return false;
    if (lastActiveState != isActive) {
        bool tmp = lastActiveState;
        lastActiveState = isActive;
        return tmp;
    }
    return this->isActive;
}

void CanvasObject::setObjectOrder(int zIndex) {
    this->objectOrder = zIndex;
    GlobalManager::getInstance()->changeObjectOrder(this);
}

int CanvasObject::getObjectOrder() {
    return objectOrder;
}

CanvasObject::CanvasObject() {
    objectOrder = 0;
    isValid = true;
    isActive = true;
    lastActiveState = false;
    objectId = GlobalManager::getInstance()->registerObject(this);
}

CanvasObject::~CanvasObject() {
    GlobalManager::getInstance()->unregisterObject(this);
}
