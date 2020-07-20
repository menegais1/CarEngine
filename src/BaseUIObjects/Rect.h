//
// Created by Roberto on 07/20/20.
//

#ifndef CARENGINE_RECT_H
#define CARENGINE_RECT_H


#include "../Base/UI/ObjectUI.h"

class Rect : public ObjectUI {
public:
    std::vector<dvec2> vertices;

    void render() override;

    Rect(Transform2D transform);

private:

};


#endif //CARENGINE_RECT_H
