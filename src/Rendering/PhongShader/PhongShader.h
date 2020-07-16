//
// Created by Roberto on 07/16/20.
//

#ifndef CARENGINE_PHONGSHADER_H
#define CARENGINE_PHONGSHADER_H


#include "../IShader.h"

class PhongShader : public IShader {
public:
    dvec3 IN_Normal[3];
    dvec3 IN_Vertices[3];
    dvec3 IN_Color[3];
    dvec3 IN_LightIntesity;
    dvec3 IN_LightPosition;
    dMatrix IN_Model;
    dMatrix IN_ModelInverse;

    dvec3 vertexShader(dvec3 vertex, int vertexIndex) override;

    dvec4 fragmentShader(dvec3 barycentric, bool &discard) override;

private:
    dvec3 UNIFORM_Color[3];
};


#endif //CARENGINE_PHONGSHADER_H
