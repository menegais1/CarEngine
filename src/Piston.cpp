//
// Created by menegais1 on 12/07/2020.
//

#include "Piston.h"


#include "Camera/Camera.h"
#include "Canvas/gl_canvas2d.h"
#include "Piston.h"

void Piston::render() {
    Object3D::render();

    //UPPER PISTON CODE
    float radius = crank->transform.scale.y;
    float l = transform.scale.z;
    float angle = crank->transform.rotation.z * PI / 180.0;
    pin->transform.position.y =
            radius * std::cos(angle) + std::sqrt(std::pow(l, 2) - (radius * radius * std::pow(sin(angle), 2) * angle)) +
            transform.scale.z + pin->transform.scale.z /2 -(pin->transform.scale.z /2 * 0.1) ;
    //LOWER PISTON CODE
    transform.position.x = crank->transform.position.x + radius * cos(angle + 90 * PI / 180);
    transform.position.y = crank->transform.position.y + radius * sin(angle + 90 * PI / 180) + transform.scale.z / 2.0;
    
    dvec2 vec = pin->transform.position - transform.position;
    angle = std::atan2(vec.y, vec.x);
    transform.rotation.z = angle * 180.0 / PI + 90;
    float deslocationInX = transform.scale.x;
    transform.position.x =
            (crank->transform.position.x + deslocationInX) + deslocationInX * cos(transform.rotation.z * (PI / 180.0));
}

Piston::Piston(Transform transform) : Cylinder(transform) {

}

