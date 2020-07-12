//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_OBJECT3D_H
#define CARENGINE_OBJECT3D_H


#include "CanvasObject.h"

class Object3D : public CanvasObject, ITransformable {
protected:
    dMatrix Model;
    dvec3 center;
    std::vector<dvec3> vertices;
    std::vector<int> triangles;

public:
    Object3D();

protected:

    void translate(dvec3 translationAmount) override;

    void rotateX(float angle) override;

    void rotateZ(float angle) override;

    void rotateY(float angle) override;

    void rescale(dvec3 scale) override;

    void computeCenter();

    void setCenter(dvec3 center);
};


#endif //CARENGINE_OBJECT3D_H
