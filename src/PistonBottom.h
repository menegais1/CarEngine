//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_PISTONBOTTOM_H
#define CARENGINE_PISTONBOTTOM_H


#include "Base3DObjects/Cylinder.h"
#include "Crank.h"

class PistonBottom : public Cylinder{
public:

    PistonBottom(Transform transform);
    Crank* crank;
    float angle;
    void render() override;

};


#endif //CARENGINE_PISTONBOTTOM_H
