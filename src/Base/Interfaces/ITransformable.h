#ifndef ITRANSFORMABLE_H
#define ITRANSFORMABLE_H

#include "../../Vectors/Vector3.h"

class ITransformable {
public:
    virtual void translate(dvec3 translationAmount) = 0;

    virtual void rotateX(float angle) = 0;

    virtual void rotateZ(float angle) = 0;

    virtual void rotateY(float angle) = 0;

    virtual void rescale(dvec3 scale) = 0;
};

#endif
