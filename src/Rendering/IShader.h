//
// Created by Roberto on 07/15/20.
//

#ifndef CARENGINE_ISHADER_H
#define CARENGINE_ISHADER_H


#include "../Vectors/Vector3.h"

class IShader {
public:
    virtual dvec3 vertexShader(dvec3 vertex) = 0;

    virtual dvec4 fragmentShader(dvec3 barycentric, bool &discard) = 0;

};


#endif //CARENGINE_ISHADER_H
