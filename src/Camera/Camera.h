//
// Created by menegais1 on 01/07/2020.
//

#ifndef PROJECTIONEXERCISE_CAMERA_H
#define PROJECTIONEXERCISE_CAMERA_H


#include <Vectors/Vector3.h>

class Camera {
public:

    static Camera *getInstance();

    dMatrix generateViewMatrix(dvec3 center, dvec3 eye, dvec3 up);

    dMatrix generateProjectionMatrix(float fov, float aspectRatio, float near, float far);

    dvec3 convertToProjectionSpace(dvec3 vertex);

    dvec3 convertNDCToViewport(dvec3 ndc);

    void setViewport(int width, int height, int x, int y);

    dMatrix translate(dvec3 translation);

    dMatrix rotateX(float angle);

    dMatrix rotateY(float angle);

    dMatrix rotateZ(float angle);

    dMatrix scale(dvec3 scale);

private:
    dvec3 center;
    dvec3 up;
    dvec3 eye;
    dMatrix View;
    dMatrix Projection;
    int Vx;
    int Vy;
    int Vheight;
    int Vwidth;

    Camera();

};


#endif //PROJECTIONEXERCISE_CAMERA_H
