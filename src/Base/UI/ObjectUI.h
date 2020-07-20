//
// Created by menegais1 on 13/07/2020.
//

#ifndef CARENGINE_OBJECTUI_H
#define CARENGINE_OBJECTUI_H


#include "../../Vectors/Vector2.h"
#include "../CanvasObject.h"
#include "Transform2D.h"

class ObjectUI : CanvasObject {
public:
    Transform2D transform;
    ObjectUI(Transform2D transform);

};


#endif //CARENGINE_OBJECTUI_H
