//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_TRANSFORM_H
#define CARENGINE_TRANSFORM_H


#include "../Vectors/Vector3.h"

class Transform {
public:
    dvec3 position;
    dvec3 rotation;
    dvec3 scale;

    Transform(const dvec3 &position, const dvec3 &rotation, const dvec3 &scale);
    Transform();
};


#endif //CARENGINE_TRANSFORM_H
