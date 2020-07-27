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

class Vertex {
public:
    dvec4 pos;
    dvec3 normal;
    dvec3 color;
    dvec3 uv;
    Vertex(const dvec4 &pos, const dvec3 &normal, const dvec3 &color,const dvec3& uv);

    Vertex();
};

class IShader {
public:
    virtual Vertex vertexShader(dvec3 vertex, int vertexIndex) = 0;

    virtual dvec4 fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) = 0;

};


#endif //CARENGINE_ISHADER_H
