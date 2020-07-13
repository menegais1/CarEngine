cmake_minimum_required(VERSION 3.16)
project(CarEngine)

set(CMAKE_CXX_STANDARD 14)

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
        src/Utilities.h src/Camera/Camera.cpp src/Camera/Camera.h src/Base3DObjects/Cube.cpp src/Base3DObjects/Cube.h src/Camera/CameraMovement.cpp src/Camera/CameraMovement.h src/Base3DObjects/Cylinder.cpp src/Base3DObjects/Cylinder.h src/Base/Object3D.cpp src/Base/Object3D.h src/Crank.cpp src/Crank.h src/Piston.cpp src/Piston.h src/Base/Transform.cpp src/Base/Transform.h)

if (WIN32)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})
    include_directories(include)
    target_link_libraries(CarEngine ${OPENGL_LIBRARIES} D:/Documents-HD/Repositories/Libraries/freeglut.lib)
endif ()

if (UNIX)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
    target_link_libraries(CarEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif ()