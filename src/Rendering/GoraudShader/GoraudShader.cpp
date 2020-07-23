//
// Created by Roberto on 07/16/20.
//

#include "GoraudShader.h"
#include "../../Camera/Camera.h"

Vertex GoraudShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec4 v = Camera::getInstance()->Projection * Camera::getInstance()->View * IN_Model * vertex;
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    float lightIntensity = std::max(0.0, (lightPosition - vertex).unit().dot(IN_Normal[vertexIndex].unit()));
    UNIFORM_Color[vertexIndex] = IN_Color[vertexIndex] * lightIntensity;
    return Vertex(v, IN_Normal[vertexIndex].unit(), UNIFORM_Color[vertexIndex]);
}

dvec4 GoraudShader::fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) {
    dvec4 color = interpVertex.color.toVector4(1);
    discard = false;
    return color;
}
