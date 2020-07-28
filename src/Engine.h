//
// Created by menegais1 on 12/07/2020.
//

#ifndef CARENGINE_ENGINE_H
#define CARENGINE_ENGINE_H


#include "Base3DObjects/Cylinder.h"

class Engine : public Object3D {
public:

    Engine(Transform transform, Cylinder *crank);

    Object3D *crank;
    std::vector<Object3D *> pistonPins;
    std::vector<Object3D *> pistons;
    std::vector<Object3D *> shirts;
    float rpm;

    void keyboard(int key) override;


private:
    bool showFaceNormals = false;
    bool showVertexNormals = false;
    bool showShirts = true;
    bool showPistons = true;
    bool showPistonPins = true;
    bool showCrank = true;

    float angularVelocity;

    void render() override;

    int pistonQuantity = 1;

    float calculateAngularVelocity(float rpm);

    dvec3 calculatePistonPinPosition(Object3D *pin, Object3D *piston, float radius, float angle, float l);

    dvec3 calculatePistonPosition(Object3D *piston, float radius, float angle) const;

    dvec3 calculatePistonRotation(Object3D *piston, dvec3 pinPosition, dvec3 pinOnCrankPosition);
};


#endif //CARENGINE_ENGINE_H
