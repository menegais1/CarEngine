//
// Created by Roberto on 07/15/20.
//

#ifndef CARENGINE_FLATSHADER_H
#define CARENGINE_FLATSHADER_H


#include "../IShader.h"

class FlatShader : public IShader {
public:
    dvec3 IN_Normal;
    dvec3 IN_Color;
    dvec3 IN_LightIntesity;
    dvec3 IN_LightPosition;
    dMatrix IN_Model;
    dMatrix IN_ModelInverse;

    virtual Vertex vertexShader(dvec3 vertex, int vertexIndex) override;

    dvec4 fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) override;

private:
    dvec3 UNIFORM_Color;
};


#endif //CARENGINE_FLATSHADER_H
