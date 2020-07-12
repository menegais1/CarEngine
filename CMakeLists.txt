cmake_minimum_required(VERSION 3.16)
project(CarEngine)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/GL)
include_directories(src)
include_directories(src/Base)
include_directories(src/Canvas)
include_directories(src/Label)
include_directories(src/Managers)
include_directories(src/Panel)
include_directories(src/Vectors)

add_executable(CarEngine
        include/GL/freeglut.h
        include/GL/freeglut_ext.h
        include/GL/freeglut_std.h
        include/GL/glut.h
        src/Base/CanvasObject.cpp
        src/Base/CanvasObject.h
        src/Base/IKeyboard.h
        src/Base/IMouse.h
        src/Base/IRender.h
        src/Base/ITransformable.h
        src/Canvas/gl_canvas2d.cpp
        src/Canvas/gl_canvas2d.h
        src/Managers/GlobalManager.cpp
        src/Managers/GlobalManager.h
        src/Vectors/Vector2.h
        src/Vectors/Vector3.h
        src/Vectors/Vector4.h
        src/Vectors/Matrix.h
        src/main.cpp
        src/Utilities.cpp
        src/Utilities.h src/Camera/Camera.cpp src/Camera/Camera.h src/Cube.cpp src/Cube.h src/Camera/CameraMovement.cpp src/Camera/CameraMovement.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(CarEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
