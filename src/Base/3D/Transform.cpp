//
// Created by menegais1 on 12/07/2020.
//

#include "Transform.h"

Transform::Transform(const dvec3 &position, const dvec3 &rotation, const dvec3 &scale) : position(position),
                                                                                         rotation(rotation),
                                                                                         scale(scale) {}

Transform::Transform() {

}
