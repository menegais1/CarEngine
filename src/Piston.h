//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_PISTON_H
#define CARENGINE_PISTON_H


#include "Base3DObjects/Cylinder.h"
#include "Crank.h"

class Piston : public Cylinder {
public:

    Piston(Transform transform);
    Object3D *crank;
    Object3D *pin;

    void render() override;

};


#endif //CARENGINE_PISTON_H
