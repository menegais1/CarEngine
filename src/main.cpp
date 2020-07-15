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
#include "Rendering/Canvas/gl_canvas2d.h"
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
                                                    0.01,
                                                    10);
    Camera::getInstance()->setViewport(GlobalManager::getInstance()->screenWidth,
                                       GlobalManager::getInstance()->screenHeight, 0, 0);
    Cube *cube = new Cube(dvec3(0, 2, 0), dvec3(1, 1, 1));
    Cylinder *crank = new Cylinder(Transform(dvec3(4, 2, 0), dvec3(0, 0, 0), dvec3(0.2, 0.2, 2)), 8);
    Engine *engine = new Engine(
            Transform(dvec3(2, 0, 0), dvec3(0, 0, 0), dvec3(1, 1, 1)), crank);
    engine->rpm = 1;

    HorizontalSlider *slider = new HorizontalSlider(dvec2(100, 30), dvec2(120, 10), dvec4(0, 0, 0, 0.2),
                                                    dvec4(0, 0, 0, 1));
    slider->setValues(1, 10000, 20);
    slider->addOnValueChangedListener([engine](float value) -> void {
        engine->rpm = value;
    });
    slider->setCurValue(engine->rpm);
    CameraMovement *cameraMovement = new CameraMovement(Camera::getInstance());
    CV::run();
}
