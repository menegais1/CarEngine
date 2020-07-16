//
// Created by Roberto on 07/15/20.
//

#ifndef CARENGINE_ISHADER_H
#define CARENGINE_ISHADER_H


#include "../Vectors/Vector3.h"


enum class ShaderType {
    Flat,
    Goraud,
    Phong
};

class IShader {
public:
    virtual dvec3 vertexShader(dvec3 vertex, int vertexIndex) = 0;

    virtual dvec4 fragmentShader(dvec3 barycentric, bool &discard) = 0;

};


#endif //CARENGINE_ISHADER_H
