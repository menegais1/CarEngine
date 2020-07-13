//
// Created by menegais1 on 01/07/2020.
//

#ifndef PROJECTIONEXERCISE_CUBE_H
#define PROJECTIONEXERCISE_CUBE_H


#include "../Base/Object3D.h"

class Cube : public Object3D {
public:

    Cube(dvec3 center, dvec3 size);

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    void keyboard(int key) override;

    void keyboardUp(int key) override;

    void setObjectOrder(int zIndex) override;

    ~Cube() override;

    void setActive(bool isActive) override;


};


#endif //PROJECTIONEXERCISE_CUBE_H
