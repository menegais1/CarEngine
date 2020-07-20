//
// Created by Roberto on 07/20/20.
//

#ifndef CARENGINE_ENGINE2D_H
#define CARENGINE_ENGINE2D_H


#include "Base/UI/ObjectUI.h"

class Engine2D : ObjectUI {
public:
    Engine2D(Transform2D transform);

    ObjectUI *crank;
    ObjectUI *pistonPin;
    ObjectUI *piston;
    float rpm;

    void render() override;

private:
    float angularVelocity;

    float calculateAngularVelocity(float rpm);

    dvec2 calculatePistonPinPosition(ObjectUI *pin, ObjectUI *piston, float radius, float angle, float l);

    double calculatePistonRotation(ObjectUI *piston, dvec2 pinPosition, dvec2 pinOnCrankPosition);

    dvec2 calculatePistonPosition(ObjectUI *piston, float radius, float angle) const;
};


#endif //CARENGINE_ENGINE2D_H
