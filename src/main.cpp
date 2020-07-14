//Roberto Menegais 201810233
/// Main class of the program, used for registering the callbacks
/// in GLUT, initialize the window, call the GlobalManager functions
/// and instantiate the program main manager
//
//Instruções para o uso do programa:
//




#include <iostream>
#include "Camera/Camera.h"
#include "Camera/CameraMovement.h"
#include "Canvas/gl_canvas2d.h"
#include "Utilities.h"
#include "Managers/GlobalManager.h"
#include "Base3DObjects/Cube.h"
#include "Base3DObjects/Cylinder.h"
#include "Engine.h"
#include "Slider/HorizontalSlider.h"

using namespace std;

void render() {
    GlobalManager::getInstance()->render();
}

void keyboard(int key) {
    GlobalManager::getInstance()->keyboard(key);
}

void keyboardUp(int key) {
    GlobalManager::getInstance()->keyboardUp(key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    GlobalManager::getInstance()->mouse(button, state, wheel, direction, x, y);
}


int main(void) {
    CV::init(GlobalManager::getInstance()->screenWidth, GlobalManager::getInstance()->screenHeight,
             "ProjectionExercise");
    dvec3 center(0, 0, 0);
    dvec3 eye = dvec3(0, 0, 5);
    Camera::getInstance()->generateViewMatrix(eye, center, dvec3(0, 1, 0));
    Camera::getInstance()->generateProjectionMatrix(60 * PI / 180.0, GlobalManager::getInstance()->screenWidth /
                                                                     (float) GlobalManager::getInstance()->screenHeight,
                                                    0.1,
                                                    10);
    Camera::getInstance()->setViewport(GlobalManager::getInstance()->screenWidth,
                                       GlobalManager::getInstance()->screenHeight, 0, 0);
    Cube *cube = new Cube(dvec3(0, 2, 0), dvec3(1, 1, 1));
    Cylinder *crank = new Cylinder(Transform(dvec3(4, 2, 0), dvec3(0, 0, 0), dvec3(0.2, 0.2, 2)), 8);
    Engine *piston = new Engine(
            Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.scale.z / 2),
                      dvec3(90, 0, 0), dvec3(0.1, 0.1, 2)));
    Cylinder *pistonPin = new Cylinder(
            Transform(crank->transform.position + dvec3(0, crank->transform.scale.y + 1, crank->transform.scale.z / 2),
                      dvec3(90, 0, 0), dvec3(0.3, 0.3, 0.5)), 30);
    piston->crank = crank;
    piston->pin = pistonPin;
    piston->rpm = 10000;

    HorizontalSlider *slider = new HorizontalSlider(dvec2(100, 30), dvec2(120, 10), dvec4(0, 0, 0, 0.2),
                                                    dvec4(0, 0, 0, 1));
    slider->setValues(1, 10000, 20);
    slider->addOnValueChangedListener([piston](float value) -> void {
        piston->rpm = value;
    });
    slider->setCurValue(piston->rpm);
    CameraMovement *cameraMovement = new CameraMovement(Camera::getInstance());
    CV::run();
}
