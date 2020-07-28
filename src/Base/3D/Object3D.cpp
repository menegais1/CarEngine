//
// Created by menegais1 on 12/07/2020.
//

#include "../../Camera/Camera.h"
#include "../../Rendering/Canvas/gl_canvas2d.h"
#include "Object3D.h"
#include "../../Utilities.h"
#include "../../Rendering/Renderer.h"
#include "../../Rendering/FlatShader/FlatShader.h"
#include "../../Rendering/GoraudShader/GoraudShader.h"
#include "../../Rendering/PhongShader/PhongShader.h"

Object3D::Object3D(Transform transform) {
    Model = dMatrix::identity(4);
    this->transform = transform;
}

void Object3D::setCenter(dvec3 center) {
    Model.setCol(center.toVector4(1), 3);
    this->transform.position = center;
}

void Object3D::computeCenter() {
    this->transform.position = dvec3(0, 0, 0);
    for (int i = 0; i < vertices.size(); ++i) {
        this->transform.position.x += vertices[i].x;
        this->transform.position.y += vertices[i].y;
        this->transform.position.z += vertices[i].z;
    }
    this->transform.position = this->transform.position / vertices.size();
    setCenter(this->transform.position);

}

dvec3 Object3D::calculateNormal(int i0, int i1, int i2) {
    dvec3 v0 = vertices[i0];
    dvec3 v1 = vertices[i1];
    dvec3 v2 = vertices[i2];
    dvec3 normal = (v1 - v0).cross(v2 - v0).unit();
    return normal;
}

void Object3D::setNormal(int i, dvec3 normal) {
    if (normals[i].equalZero()) normals[i] = normal;
    else normals[i] = (normals[i] + normal) / 2;
}

void Object3D::createRenderingShader(ShaderType shaderType) {
    if (shaderType == ShaderType::Flat) {
        FlatShader *flatShader = new FlatShader();
        flatShader->IN_Color = dvec3(0.8, 0.8, 0.8);
        flatShader->IN_LightPosition = dvec3(0, 2, 0);
        flatShader->IN_Model = Model;
        flatShader->IN_ModelInverse = InvModel;
        shader = flatShader;
    }
    if (shaderType == ShaderType::Goraud) {
        GoraudShader *goraudShader = new GoraudShader();
        goraudShader->IN_LightPosition = dvec3(0, 2, 0);
        goraudShader->IN_Model = Model;
        goraudShader->IN_ModelInverse = InvModel;
        shader = goraudShader;
    }
    if (shaderType == ShaderType::Phong) {
        PhongShader *phongShader = new PhongShader();
        phongShader->IN_LightPosition = dvec3(0, 2, 0);
        phongShader->IN_Model = Model;
        phongShader->IN_ModelInverse = InvModel;
        shader = phongShader;
    }
}

void Object3D::setRenderingShaderInfo(ShaderType shaderType, int i) {
    if (shaderType == ShaderType::Flat) {
        FlatShader *flatShader = (FlatShader *) shader;
        dvec3 v0 = vertices[faces[i].vertices[0]];
        dvec3 v1 = vertices[faces[i].vertices[1]];
        dvec3 v2 = vertices[faces[i].vertices[2]];
        dvec3 normal = (v1 - v0).cross(v2 - v0);
        flatShader->IN_Normal = normal;
        flatShader->IN_UV[0] = uvs[faces[i].uv[0]];
        flatShader->IN_UV[1] = uvs[faces[i].uv[1]];
        flatShader->IN_UV[2] = uvs[faces[i].uv[2]];
        flatShader->IN_Albedo = albedo;
    }
    if (shaderType == ShaderType::Goraud) {
        GoraudShader *goraudShader = (GoraudShader *) shader;
        goraudShader->IN_Normal[0] = normals[faces[i].normals[0]];
        goraudShader->IN_Normal[1] = normals[faces[i].normals[1]];
        goraudShader->IN_Normal[2] = normals[faces[i].normals[2]];
        goraudShader->IN_Color[0] = dvec3(0.8, 0.8, 0.8);
        goraudShader->IN_Color[1] = dvec3(0.8, 0.8, 0.8);
        goraudShader->IN_Color[2] = dvec3(0.8, 0.8, 0.8);
        goraudShader->IN_UV[0] = uvs[faces[i].uv[0]];
        goraudShader->IN_UV[1] = uvs[faces[i].uv[1]];
        goraudShader->IN_UV[2] = uvs[faces[i].uv[2]];
        goraudShader->IN_CameraPosition = Camera::getInstance()->center;
        goraudShader->IN_Albedo = albedo;
        goraudShader->IN_Specular = specular;
        goraudShader->IN_SpecularModifier = 100;
    }
    if (shaderType == ShaderType::Phong) {
        PhongShader *phongShader = (PhongShader *) shader;
        phongShader->IN_Normal[0] = normals[faces[i].normals[0]];
        phongShader->IN_Normal[1] = normals[faces[i].normals[1]];
        phongShader->IN_Normal[2] = normals[faces[i].normals[2]];
        phongShader->IN_Vertices[0] = vertices[faces[i].vertices[0]];
        phongShader->IN_Vertices[1] = vertices[faces[i].vertices[1]];
        phongShader->IN_Vertices[2] = vertices[faces[i].vertices[2]];
        phongShader->IN_Color[0] = dvec3(0.8, 0.8, 0.8);
        phongShader->IN_Color[1] = dvec3(0.8, 0.8, 0.8);
        phongShader->IN_Color[2] = dvec3(0.8, 0.8, 0.8);
        phongShader->IN_UV[0] = uvs[faces[i].uv[0]];
        phongShader->IN_UV[1] = uvs[faces[i].uv[1]];
        phongShader->IN_UV[2] = uvs[faces[i].uv[2]];
        phongShader->IN_CameraPosition = Camera::getInstance()->center;
        phongShader->IN_Albedo = albedo;
        phongShader->IN_Specular = specular;
        phongShader->IN_SpecularModifier = 100;

    }

}

void Object3D::render() {
    if (faces.size() == 0) return;
    if (std::abs(transform.rotation.x) >= 360) transform.rotation.x = (int) transform.rotation.x % 360;
    if (std::abs(transform.rotation.y) >= 360) transform.rotation.y = (int) transform.rotation.y % 360;
    if (std::abs(transform.rotation.z) >= 360) transform.rotation.z = (int) transform.rotation.z % 360;

    auto S = dMatrix::scale(transform.scale);
    auto T = dMatrix::translate(transform.position);
    auto Rx = dMatrix::rotateX(transform.rotation.x * PI / 180.0);
    auto Ry = dMatrix::rotateY(transform.rotation.y * PI / 180.0);
    auto Rz = dMatrix::rotateZ(transform.rotation.z * PI / 180.0);
    Model = T * Rz * Ry * Rx * S;
    InvModel = Model.invert();
    dvec3 cameraPos = (InvModel * Camera::getInstance()->center).toVector3();
    CV::color(1, 1, 1, 1);
    createRenderingShader(Renderer::getInstance()->shaderType);
    int cont = 0;
    for (int i = 0; i < faces.size(); i++) {
        cont++;
        dvec3 v0 = vertices[faces[i].vertices[0]];
        dvec3 v1 = vertices[faces[i].vertices[1]];
        dvec3 v2 = vertices[faces[i].vertices[2]];
        dvec3 normal = (v1 - v0).cross(v2 - v0).unit();
        dvec3 modelCenter = (v0 + v1 + v2) / 3.0;
        if (Renderer::getInstance()->isActive) {
            if (normal.dot((cameraPos - v0).unit()) < 0) continue;
            setRenderingShaderInfo(Renderer::getInstance()->shaderType, i);
            Vertex vs0 = shader->vertexShader(v0, 0);
            Vertex vs1 = shader->vertexShader(v1, 1);
            Vertex vs2 = shader->vertexShader(v2, 2);
            Renderer::getInstance()->triangle(vs0, vs1, vs2, shader);
        } else {

            if (showFaceNormals) {
                CV::color(1, 0, 0, 1);
                Camera::getInstance()->line((Model * modelCenter).toVector3(), (Model * (modelCenter + normal)).toVector3());
            }
            if (showVertexNormals) {
                CV::color(0, 1, 0, 1);
                Camera::getInstance()->line((Model * v0).toVector3(), (Model * (v0 + normals[faces[i].normals[0]])).toVector3());
                Camera::getInstance()->line((Model * v1).toVector3(), (Model * (v1 + normals[faces[i].normals[1]])).toVector3());
                Camera::getInstance()->line((Model * v2).toVector3(), (Model * (v2 + normals[faces[i].normals[2]])).toVector3());
            }
            CV::color(0, 0, 0, 1);
            Camera::getInstance()->line((Model * v0.toVector4(1)).toVector3(), (Model * v1.toVector4(1)).toVector3());
            Camera::getInstance()->line((Model * v1.toVector4(1)).toVector3(), (Model * v2.toVector4(1)).toVector3());
            Camera::getInstance()->line((Model * v2.toVector4(1)).toVector3(), (Model * v0.toVector4(1)).toVector3());
        }

    }
    delete shader;
}

