//
// Created by Roberto on 07/15/20.
//

#include "IShader.h"

Vertex::Vertex(const dvec4 &pos, const dvec3 &normal, const dvec3 &color, const dvec3 &uv) : pos(pos), normal(normal),
                                                                                             color(color), uv(uv) {}

Vertex::Vertex() {}
