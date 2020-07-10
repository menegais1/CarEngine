#ifndef ITRANSFORMABLE_H
#define ITRANSFORMABLE_H

#include "../Vectors/Vector3.h"

class ITransformable {
public:
    virtual void translate(dvec3) = 0;

    virtual void rotate(float, dvec3) = 0;

    virtual void rescale(dvec3, dvec3) = 0;
};

#endif
