//
// Created by Roberto on 07/15/20.
//

#include "FlatShader.h"
#include "../../Camera/Camera.h"

Vertex FlatShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec4 v = Camera::getInstance()->Projection *Camera::getInstance()->View * IN_Model * vertex;
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    float lightIntensity = std::max(0.0, (lightPosition - vertex).unit().dot(IN_Normal.unit()));
    UNIFORM_Color = IN_Color * lightIntensity;
    return Vertex(v,IN_Normal,UNIFORM_Color);
}

dvec4 FlatShader::fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) {
    discard = false;
    return interpVertex.color.toVector4(1);
}
