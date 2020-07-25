//
// Created by Roberto on 07/16/20.
//

#include "PhongShader.h"
#include "../../Camera/Camera.h"

Vertex PhongShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec4 v = Camera::getInstance()->Projection * Camera::getInstance()->View * IN_Model * vertex;
    return Vertex(v, IN_Normal[vertexIndex].unit(), IN_Color[vertexIndex]);
}

dvec4 PhongShader::fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) {
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    dvec3 vertexPos = IN_Vertices[0] * barycentric[0] + IN_Vertices[1] * barycentric[1] + IN_Vertices[2] * barycentric[2];
    dvec3 normal =interpVertex.normal;
    float lightIntensity = std::max(0.0, (lightPosition - vertexPos).unit().dot(normal.unit()));
    dvec3 color = interpVertex.color;
    return (color * (lightIntensity + 0.2)).toVector4(1);
}
