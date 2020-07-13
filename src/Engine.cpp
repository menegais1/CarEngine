//
// Created by menegais1 on 12/07/2020.
//

#include "Engine.h"


#include "Camera/Camera.h"
#include "Canvas/gl_canvas2d.h"
#include "Managers/GlobalManager.h"
#include "Engine.h"

float Engine::calculateAngularVelocity(float rpm) {
    return (2.0 * PI * rpm) / 60.0;
}

void Engine::render() {
    Object3D::render();
    angularVelocity = calculateAngularVelocity(rpm);
    crank->transform.rotation.z += angularVelocity * GlobalManager::getInstance()->deltaTime;
    dvec3 pinPosition = pin->transform.position;
    dvec3 pinOnCrankPosition = transform.position;
    //UPPER PISTON CODE
    float radius = crank->transform.scale.y;
    float l = transform.scale.z;
    float angle = crank->transform.rotation.z * PI / 180.0;
    pinPosition.y =
            radius * std::cos(angle) + std::sqrt(std::pow(l, 2) - (radius * radius * std::pow(sin(angle), 2) * angle)) +
            transform.scale.z + pin->transform.scale.z / 2 - (pin->transform.scale.z / 2 * 0.1);
    //LOWER PISTON CODE
    pinOnCrankPosition.x = crank->transform.position.x + radius * cos(angle + 90 * PI / 180);
    pinOnCrankPosition.y = crank->transform.position.y + radius * sin(angle + 90 * PI / 180);
    transform.position = ((pinPosition + pinOnCrankPosition) / 2);
    transform.position.y -= pin->transform.scale.z / 4;
    dvec2 vec = pinPosition - pinOnCrankPosition;
    angle = std::atan2(vec.y, vec.x);
    transform.rotation.z = angle * 180.0 / PI + 90;
    pin->transform.position = pinPosition;
}

Engine::Engine(Transform transform) : Cylinder(transform) {
    rpm = 100;
}

