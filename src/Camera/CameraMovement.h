//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_CAMERAMOVEMENT_H
#define CARENGINE_CAMERAMOVEMENT_H


#include "../Base/CanvasObject.h"
#include "Camera.h"

class CameraMovement : public CanvasObject {
private:
    Camera* camera;
    dvec2 lastMousePosition;
    bool isDragging = false;
    dvec2 angle;
public:

    CameraMovement(Camera *camera);

    void keyboard(int key) override;

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void translate(dvec3 dvec31) override;

    void rotate(float d, dvec3 dvec31) override;

    void rescale(dvec3 dvec31, dvec3 dvec32) override;

    bool pointIntersectsObject(dvec3 point) override;
};


#endif //CARENGINE_CAMERAMOVEMENT_H
