//
// Created by menegais1 on 01/07/2020.
//

#ifndef PROJECTIONEXERCISE_CAMERA_H
#define PROJECTIONEXERCISE_CAMERA_H


#include "../Vectors/Vector3.h"

class Camera {
public:

    static Camera *getInstance();

    dMatrix generateViewMatrix(dvec3 eye, dvec3 at, dvec3 up);

    dMatrix generateProjectionMatrix(float fov, float aspectRatio, float near, float far);

    dvec3 convertNDCToViewport(dvec3 ndc);

    void setViewport(int width, int height, int x, int y);

    dvec3 clipCoordinates(dvec3 vertex);

    dvec3 convertViewToProjection(dvec3 vertex);

    dvec3 convertWorldToView(dvec3 vertex);

    dvec3 removeBackCameraVertex(dvec3 vertex);

    dvec3 convertModelToViewport(dvec3 vertex, dMatrix Model);

    dvec3 center;
    dvec3 up;
    dvec3 forward;
    dvec3 right;
    dvec3 at;
private:
    dMatrix View;
    dMatrix Projection;
    int Vx;
    int Vy;
    int Vheight;
    int Vwidth;

    Camera();


};


#endif //PROJECTIONEXERCISE_CAMERA_H
