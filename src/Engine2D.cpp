#include "Engine2D.h"
#include "Managers/GlobalManager.h"
#include "BaseUIObjects/Rect.h"

float Engine2D::calculateAngularVelocity(float rpm) {
    return (2.0 * PI * rpm) / 60.0;
}

dvec2 Engine2D::calculatePistonPinPosition(ObjectUI *pin, ObjectUI *piston, float radius, float angle, float l) {
    dvec2 pinPosition = pin->transform.position;
    pinPosition.y =
            radius * std::cos(angle) + std::sqrt((l * l) - ((radius * radius) * (std::sin(angle) * std::sin(angle))));
    return pinPosition;
}

dvec2 Engine2D::calculatePistonPosition(ObjectUI *piston, float radius, float angle) const {
    dvec2 pinOnCrankPosition = piston->transform.position;
    pinOnCrankPosition.x = crank->transform.position.x + radius * cos(angle + 90 * PI / 180);
    pinOnCrankPosition.y = crank->transform.position.y + radius * sin(angle + 90 * PI / 180);

    return pinOnCrankPosition;
}

double Engine2D::calculatePistonRotation(ObjectUI *piston, dvec2 pinPosition, dvec2 pinOnCrankPosition) {
    dvec2 vec = pinPosition - pinOnCrankPosition;
    float angle = std::atan2(vec.y, vec.x);
    double rotation = angle * 180.0 / PI + 90;
    return rotation;
};

void Engine2D::render() {
    angularVelocity = calculateAngularVelocity(rpm);
    crank->transform.rotation += angularVelocity * GlobalManager::getInstance()->deltaTime;
    float radius = crank->transform.scale.y / 2;
    float angle = crank->transform.rotation * PI / 180.0;
    float l = piston->transform.scale.y;
    dvec2 pinPosition = calculatePistonPinPosition(pistonPin, piston, radius, angle, l) + dvec2(0,crank->transform.position.y);
    dvec2 pistonPosition = calculatePistonPosition(piston, radius, angle);
    double pistonRotation = calculatePistonRotation(piston, pinPosition, pistonPosition);
    piston->transform.position = ((pinPosition + pistonPosition) / 2);
    piston->transform.rotation = pistonRotation;
    pistonPin->transform.position = pinPosition;

}

Engine2D::Engine2D(Transform2D transform) : ObjectUI(transform) {
    crank = new Rect(Transform2D(transform.position + dvec2(0, -transform.scale.y / 2), 0, dvec2(20, 20)));
    piston = new Rect(Transform2D(crank->transform.position + dvec2(0, crank->transform.scale.y / 2 + 40), 0, dvec2(10, 80)));
    pistonPin = new Rect(Transform2D(piston->transform.position + dvec2(0, crank->transform.scale.y / 2), 0, dvec2(30, 30)));
}
