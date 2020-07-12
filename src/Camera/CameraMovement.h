//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_CAMERAMOVEMENT_H
#define CARENGINE_CAMERAMOVEMENT_H


#include "../Base/CanvasObject.h"
#include "Camera.h"

class CameraMovement : public CanvasObject {
private:
    Camera *camera;
    dvec2 lastMousePosition;
    bool isDragging = false;
    dvec2 angle;
public:

    CameraMovement(Camera *camera);

    void keyboard(int key) override;

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

};


#endif //CARENGINE_CAMERAMOVEMENT_H
