//
// Created by Roberto on 07/16/20.
//

#include "GoraudShader.h"
#include "../../Camera/Camera.h"

dvec3 GoraudShader::vertexShader(dvec3 vertex, int vertexIndex) {
//    dvec3 v = Camera::getInstance()->convertModelToViewport(vertex, IN_Model);
    dvec3 v = dvec3(0,0,0);
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    float lightIntensity = std::max(0.0, (lightPosition - vertex).unit().dot(IN_Normal[vertexIndex].unit()));
    UNIFORM_Color[vertexIndex] = IN_Color[vertexIndex] * lightIntensity;
    return v;
}

dvec4 GoraudShader::fragmentShader(dvec3 barycentric, bool &discard) {
    dvec4 color = (UNIFORM_Color[0] * barycentric[0] + UNIFORM_Color[1] * barycentric[1] + UNIFORM_Color[2] * barycentric[2]).toVector4(1);
    discard = false;
    return color;
}
