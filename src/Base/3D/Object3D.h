//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_OBJECT3D_H
#define CARENGINE_OBJECT3D_H


#include "../CanvasObject.h"
#include "Transform.h"

class Object3D : public CanvasObject {
protected:
    Object3D(Transform transform);

    dMatrix Model;
    std::vector<dvec3> vertices;
    std::vector<int> triangles;

    void computeCenter();

    void setCenter(dvec3 center);

    void render() override;

public:
    Transform transform;


};


#endif //CARENGINE_OBJECT3D_H
