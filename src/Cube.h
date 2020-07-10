//
// Created by menegais1 on 01/07/2020.
//

#ifndef PROJECTIONEXERCISE_CUBE_H
#define PROJECTIONEXERCISE_CUBE_H


#include <Base/CanvasObject.h>

class Cube : public CanvasObject{
public:
    std::vector<dvec3> vertices;
    Cube(dvec3 center, dvec3 size);

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    void keyboard(int key) override;

    void keyboardUp(int key) override;

    void setObjectOrder(int zIndex) override;

    ~Cube() override;

    void setActive(bool isActive) override;

    bool pointIntersectsObject(dvec3 point) override;

    void translate(dvec3 translationAmount) override;

    void rotate(float d, dvec3 dvec31) override;

    void rescale(dvec3 dvec31, dvec3 dvec32) override;
};


#endif //PROJECTIONEXERCISE_CUBE_H
