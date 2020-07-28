//
// Created by Roberto on 07/16/20.
//

#include "GoraudShader.h"
#include "../../Camera/Camera.h"

Vertex GoraudShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec4 v = Camera::getInstance()->Projection * Camera::getInstance()->View * IN_Model * vertex;
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    dvec3 cameraPosition = (IN_ModelInverse * IN_CameraPosition.toVector4(1)).toVector3();
    float diffuse = std::max(0.0, (lightPosition - vertex).unit().dot(IN_Normal[vertexIndex].unit()));
    if (IN_Albedo != nullptr) {
        IN_Color[vertexIndex] = IN_Albedo->sampleBitmao(IN_UV[vertexIndex].x, IN_UV[vertexIndex].y) / 255.0;
    }
    float specular = 0;
    dvec3 l = (lightPosition - vertex).unit();
    IN_Normal[vertexIndex] = IN_Normal[vertexIndex].unit();
    dvec3 r = (IN_Normal[vertexIndex] * (IN_Normal[vertexIndex].dot(l) * 2.f) - l).unit();
    float specularModifier = std::abs((r).unit().dot((cameraPosition - vertex).unit()));
    if (IN_Specular != nullptr) {
        specular = std::pow(specularModifier,
                            IN_Specular->sampleBitmao(IN_UV[vertexIndex].x, IN_UV[vertexIndex].y).x);
    } else {
        specular = std::pow(specularModifier, IN_SpecularModifier);
    }
    UNIFORM_Color[vertexIndex] = IN_Color[vertexIndex] * (diffuse + 0.2) + dvec3(1, 1, 1) * specular * diffuse;
    return Vertex(v, IN_Normal[vertexIndex].unit(), UNIFORM_Color[vertexIndex], IN_UV[vertexIndex]);
}

dvec4 GoraudShader::fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) {
    dvec4 color = interpVertex.color.toVector4(1);
    discard = false;
    return color;
}
