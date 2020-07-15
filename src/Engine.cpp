//
// Created by menegais1 on 12/07/2020.
//

#include "Engine.h"


#include "Camera/Camera.h"
#include "Rendering/Canvas/gl_canvas2d.h"
#include "Managers/GlobalManager.h"
#include "Engine.h"

float Engine::calculateAngularVelocity(float rpm) {
    return (2.0 * PI * rpm) / 60.0;
}

dvec3 Engine::calculatePistonPinPosition(Object3D *pin, Object3D *piston, float radius, float angle, float l) {
    dvec3 pinPosition = pin->transform.position;
    pinPosition.y =
            radius * std::cos(angle) + std::sqrt(std::pow(l, 2) - (radius * radius * std::pow(sin(angle), 2) * angle)) +
            l + pin->transform.scale.z / 2 - (pin->transform.scale.z / 2 * 0.1);
    return pinPosition;
}

dvec3 Engine::calculatePistonPosition(Object3D *piston, float radius, float angle) const {
    dvec3 pinOnCrankPosition = piston->transform.position;
    pinOnCrankPosition.x = crank->transform.position.x + radius * cos(angle + 90 * PI / 180);
    pinOnCrankPosition.y = crank->transform.position.y + radius * sin(angle + 90 * PI / 180);

    return pinOnCrankPosition;
}

dvec3 Engine::calculatePistonRotation(Object3D *piston, dvec3 pinPosition, dvec3 pinOnCrankPosition) {
    dvec2 vec = pinPosition - pinOnCrankPosition;
    float angle = std::atan2(vec.y, vec.x);
    dvec3 rotation = piston->transform.rotation;
    rotation.z = angle * 180.0 / PI + 90;
    return rotation;
};

void Engine::render() {
    Object3D::render();
    angularVelocity = calculateAngularVelocity(rpm);
    crank->transform.rotation.z += angularVelocity * GlobalManager::getInstance()->deltaTime;
    float radius = crank->transform.scale.y;

    for (int i = 0; i < pistons.size(); ++i) {
        float angle = crank->transform.rotation.z * PI / 180.0;
        if (i % 2 != 0) angle = angle + 180 * PI / 180.0;
        float l = pistons[i]->transform.scale.z;
        dvec3 pinPosition = calculatePistonPinPosition(pistonPins[i], pistons[i], radius, angle, l);
        dvec3 pistonPosition = calculatePistonPosition(pistons[i], radius, angle);
        dvec3 pistonRotation = calculatePistonRotation(pistons[i], pinPosition, pistonPosition);
        pistons[i]->transform.position = ((pinPosition + pistonPosition) / 2);
        pistons[i]->transform.position.y -= pistonPins[i]->transform.scale.z / 4;
        pistons[i]->transform.rotation = pistonRotation;
        pistonPins[i]->transform.position = pinPosition;
    }
}

Engine::Engine(Transform transform, Cylinder *crank) : Object3D(transform) {
    rpm = 100;
    this->crank = crank;
    pistons.push_back(new Cylinder(Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.position.z + crank->transform.scale.z / 2),
                                             dvec3(90, 0, 0), dvec3(0.1, 0.1, 2)), 30));
    pistonPins.push_back(new Cylinder(Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.position.z + crank->transform.scale.z / 2),
                                                dvec3(90, 0, 0), dvec3(0.3, 0.3, 0.5)), 30));
//    pistons.push_back(new Cylinder(Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.position.z),
//                                             dvec3(90, 0, 0), dvec3(0.1, 0.1, 2)), 30));
//    pistonPins.push_back(new Cylinder(Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.position.z),
//                                                dvec3(90, 0, 0), dvec3(0.3, 0.3, 0.5)), 30));
//    pistons.push_back(new Cylinder(Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.position.z - crank->transform.scale.z / 2),
//                                             dvec3(90, 0, 0), dvec3(0.1, 0.1, 2)), 30));
//    pistonPins.push_back(new Cylinder(Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.position.z - crank->transform.scale.z / 2),
//                                                dvec3(90, 0, 0), dvec3(0.3, 0.3, 0.5)), 30));
}

