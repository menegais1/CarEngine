//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_CRANK_H
#define CARENGINE_CRANK_H


#include "Base3DObjects/Cylinder.h"

class Crank : public Cylinder {
public:

    Crank(Transform transform);

    void render() override;

    double angle = 0;
};


#endif //CARENGINE_CRANK_H
