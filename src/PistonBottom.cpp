//
// Created by menegais1 on 12/07/2020.
//

#include "PistonBottom.h"


#include "Camera/Camera.h"
#include "Canvas/gl_canvas2d.h"
#include "PistonBottom.h"

void PistonBottom::render() {
    Object3D::render();

    //UPPER PISTON CODE
    float radius = crank->transform.scale.y;
    float l = transform.scale.z;
    float angle = crank->transform.rotation.z * PI / 180.0;
    transform.position.y =
            radius * std::cos(angle) + std::sqrt(std::pow(l, 2) - (radius * radius * std::pow(sin(angle), 2) * angle));
    //LOWER PISTON CODE
    dvec2 vec = crank->transform.position - transform.position;
    transform.position.x = crank->transform.position.x + radius * cos(angle);
    transform.position.y = crank->transform.position.y + radius * sin(angle);

    angle = -std::atan2(vec.y, vec.x);
    transform.rotation.z = angle * 180.0 / PI;
}

PistonBottom::PistonBottom(Transform transform) : Cylinder(transform) {

}

