//
// Created by Roberto on 07/16/20.
//

#include "PhongShader.h"
#include "../../Camera/Camera.h"

Vertex PhongShader::vertexShader(dvec3 vertex, int vertexIndex) {
    dvec4 v = Camera::getInstance()->Projection * Camera::getInstance()->View * IN_Model * vertex;
    return Vertex(v, IN_Normal[vertexIndex].unit(), IN_Color[vertexIndex], IN_UV[vertexIndex]);
}

dvec4 PhongShader::fragmentShader(Vertex interpVertex, dvec3 barycentric, bool &discard) {
    dvec3 lightPosition = (IN_ModelInverse * IN_LightPosition.toVector4(1)).toVector3();
    dvec3 cameraPosition = (IN_ModelInverse * IN_CameraPosition.toVector4(1)).toVector3();
    dvec3 vertexPos =
            IN_Vertices[0] * barycentric[0] + IN_Vertices[1] * barycentric[1] + IN_Vertices[2] * barycentric[2];
    dvec3 normal = interpVertex.normal.unit();
    float diffuse = std::max(0.0, (lightPosition - vertexPos).unit().dot(normal.unit()));
    dvec3 color = interpVertex.color;
    if (IN_Albedo != nullptr) {
        color = IN_Albedo->sampleBitmao(interpVertex.uv.x, interpVertex.uv.y) / 255.0;
    }
    float specular = 0;
    dvec3 l = (lightPosition - vertexPos).unit();
    dvec3 r = (normal * (normal.dot(l) * 2.f) - l).unit();
    float specularModifier = std::abs((r).unit().dot((cameraPosition - vertexPos).unit()));
    if (IN_Specular != nullptr) {
        specular = std::pow(specularModifier,
                            IN_Specular->sampleBitmao(interpVertex.uv.x, interpVertex.uv.y).x);
    } else {
        specular = std::pow(specularModifier, IN_SpecularModifier);
    }
    color = color * (diffuse + 0.2) + dvec3(1, 1, 1) * specular * diffuse;
    return color.toVector4(1);
}
