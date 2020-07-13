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
#include "Crank.h"
#include "PistonBottom.h"

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
    Crank *crank = new Crank(Transform(dvec3(4, 2, 0), dvec3(0, 0, 0), dvec3(0.2, 0.2, 2)));
    PistonBottom *pistonBottom = new PistonBottom(Transform(crank->transform.position + dvec3(0,crank->transform.scale.y + 1,crank->transform.scale.z / 2), dvec3(90, 0, 0), dvec3(0.1, 0.1, 2)));
    pistonBottom->crank = crank;
    CameraMovement *cameraMovement = new CameraMovement(Camera::getInstance());
    CV::run();
}