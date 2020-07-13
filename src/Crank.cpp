//
// Created by menegais1 on 12/07/2020.
//

#include "Camera/Camera.h"
#include "Canvas/gl_canvas2d.h"
#include "Crank.h"

void Crank::render() {
    Object3D::render();
    this->transform.rotation.z -= 2;

}

Crank::Crank(Transform transform) : Cylinder(transform) {

}
