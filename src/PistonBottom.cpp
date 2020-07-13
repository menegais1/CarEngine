//
// Created by menegais1 on 12/07/2020.
//

#include "PistonBottom.h"


#include "Camera/Camera.h"
#include "Canvas/gl_canvas2d.h"
#include "PistonBottom.h"

void PistonBottom::render() {
    Object3D::render();
    dvec3 position = transform.position;
    position.y = transform.position.y - transform.scale.z / 2;
    auto T = dMatrix::translate(-crank->transform.position);
    auto rotation = dMatrix::rotateZ(0.01);
    auto Tinv = dMatrix::translate(crank->transform.position);
    position = (Tinv * rotation * T * position.toVector4(1)).toVector3();
    position.y = position.y + transform.scale.z / 2;
    transform.position = position;
}

PistonBottom::PistonBottom(Transform transform) : Cylinder(transform) {

}

