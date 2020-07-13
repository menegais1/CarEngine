//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_ENGINE_H
#define CARENGINE_ENGINE_H


#include "Base3DObjects/Cylinder.h"

class Engine : public Cylinder {
public:

    Engine(Transform transform);

    Object3D *crank;
    Object3D *pin;

    float rpm;
private:
    float angularVelocity;

    void render() override;

    float calculateAngularVelocity(float rpm);
};


#endif //CARENGINE_ENGINE_H
