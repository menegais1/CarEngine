//
// Created by Roberto on 07/20/20.
//

#include "Rect.h"
#include "../Rendering/Canvas/gl_canvas2d.h"

void Rect::render() {
    if (std::abs(transform.rotation) >= 360)
        transform.rotation = (int) transform.rotation % 360;
    dvec2 p0, p1;
    for (int i = 0; i < vertices.size() - 1; ++i) {
        p0 = vertices[i];
        p1 = vertices[i + 1];
        p0 = rotatePoint2D(dvec2(p0.x * transform.scale.x, p0.y * transform.scale.y), transform.rotation * PI / 180.0) + transform.position;
        p1 = rotatePoint2D(dvec2(p1.x * transform.scale.x, p1.y * transform.scale.y), transform.rotation * PI / 180.0) + transform.position;
        CV::line(p0, p1);
    }

    p0 = vertices[vertices.size() - 1];
    p1 = vertices[0];
    p0 = rotatePoint2D(dvec2(p0.x * transform.scale.x, p0.y * transform.scale.y), transform.rotation * PI / 180.0) + transform.position;
    p1 = rotatePoint2D(dvec2(p1.x * transform.scale.x, p1.y * transform.scale.y), transform.rotation * PI / 180.0) + transform.position;
    CV::line(p0, p1);
}

Rect::Rect(Transform2D transform) : ObjectUI(transform) {
    vertices.push_back(dvec2(-0.5, -0.5));
    vertices.push_back(dvec2(+0.5, -0.5));
    vertices.push_back(dvec2(+0.5, +0.5));
    vertices.push_back(dvec2(-0.5, +0.5));
}
