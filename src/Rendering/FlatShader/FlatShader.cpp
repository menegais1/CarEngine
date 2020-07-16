//
// Created by Roberto on 07/15/20.
//

#include "FlatShader.h"
#include "../../Camera/Camera.h"

dvec3 FlatShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec3 v = Camera::getInstance()->convertModelToViewport(vertex, IN_Model);
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    float lightIntensity = std::max(0.0, (lightPosition - vertex).unit().dot(IN_Normal.unit()));
    UNIFORM_Color = IN_Color * lightIntensity;
    return v;
}

dvec4 FlatShader::fragmentShader(dvec3 barycentric, bool &discard) {
    discard = false;
    return UNIFORM_Color.toVector4(1);
}
