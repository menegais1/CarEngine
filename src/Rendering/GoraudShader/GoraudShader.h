//
// Created by Roberto on 07/16/20.
//

#ifndef CARENGINE_GORAUDSHADER_H
#define CARENGINE_GORAUDSHADER_H


#include "../../Vectors/Vector3.h"
#include "../IShader.h"
#include "../../Bitmap/Bitmap.h"

class GoraudShader : public IShader {
public:
    Bitmap* IN_Albedo;
    Bitmap* IN_Specular;
    float IN_SpecularModifier;
    dvec3 IN_UV[3];
    dvec3 IN_Normal[3];
    dvec3 IN_Color[3];
    dvec3 IN_CameraPosition;
    dvec3 IN_LightPosition;
    dMatrix IN_Model;
    dMatrix IN_ModelInverse;

    virtual Vertex vertexShader(dvec3 vertex, int vertexIndex) override;

    dvec4 fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) override;

private:
    dvec3 UNIFORM_Color[3];
};


#endif //CARENGINE_GORAUDSHADER_H
