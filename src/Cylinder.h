//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_CYLINDER_H
#define CARENGINE_CYLINDER_H


#include "Base/Object3D.h"
#include "Vectors/Vector3.h"

class Cylinder : public Object3D {
public:
    float radius;
    float height;

    Cylinder(dvec3 center, float radius, float height);

    void render() override;

};


#endif //CARENGINE_CYLINDER_H
