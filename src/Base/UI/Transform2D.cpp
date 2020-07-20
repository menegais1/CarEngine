//
// Created by menegais1 on 12/07/2020.
//

#include "Transform2D.h"

Transform2D::Transform2D(const dvec2 &position, const double &rotation, const dvec2 &scale) : position(position),
                                                                                         rotation(rotation),
                                                                                         scale(scale) {}

Transform2D::Transform2D() {

}
