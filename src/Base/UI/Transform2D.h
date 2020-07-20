//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_TRANSFORM2D_H
#define CARENGINE_TRANSFORM2D_H


#include "../../Vectors/Vector2.h"

class Transform2D {
public:
    dvec2 position;
    double rotation;
    dvec2 scale;

    Transform2D(const dvec2 &position, const double &rotation, const dvec2 &scale);
    Transform2D();
};


#endif //CARENGINE_TRANSFORM_H
