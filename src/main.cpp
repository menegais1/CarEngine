//Roberto Menegais 201810233
/// Main class of the program, used for registering the callbacks
/// in GLUT, initialize the window, call the GlobalManager functions
/// and instantiate the program main manager
//
//Instruções para o uso do programa:
//




#include <iostream>
#include <Camera/Camera.h>
#include "Canvas/gl_canvas2d.h"
#include "Utilities.h"
#include "Managers/GlobalManager.h"
#include "Cube.h"

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
    dvec3 center(0, 0, 5);
    dvec3 eye = dvec3(0, 0, 0) - center;
    Camera::getInstance()->generateViewMatrix(center, eye, dvec3(0, 1, 0));
    Camera::getInstance()->generateProjectionMatrix(10);
    Camera::getInstance()->generateViewPortMatrix(*GlobalManager::getInstance()->screenWidth / 2,
                                                  *GlobalManager::getInstance()->screenHeight / 2, 10, 10);
    Cube *cube = new Cube(dvec3(0, 0, 0), dvec3(1, 1, 1));
    CV::run();
}
