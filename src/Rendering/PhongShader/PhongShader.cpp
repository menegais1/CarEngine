//
// Created by Roberto on 07/16/20.
//

#include "PhongShader.h"
#include "../../Camera/Camera.h"

dvec3 PhongShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec3 v = Camera::getInstance()->convertModelToViewport(vertex, IN_Model);
    return v;
}

dvec4 PhongShader::fragmentShader(dvec3 barycentric, bool &discard) {
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    dvec3 vertexPos = IN_Vertices[0] * barycentric[0] + IN_Vertices[1] * barycentric[1] + IN_Vertices[2] * barycentric[2];
    dvec3 normal = IN_Normal[0] * barycentric[0] + IN_Normal[1] * barycentric[1] + IN_Normal[2] * barycentric[2];
    float lightIntensity = std::max(0.0, (lightPosition - vertexPos).unit().dot(normal.unit()));
    dvec3 color = (IN_Color[0] * barycentric[0] + IN_Color[1] * barycentric[1] + IN_Color[2] * barycentric[2]).toVector4(1);
    return (color * lightIntensity).toVector4(1);
}
