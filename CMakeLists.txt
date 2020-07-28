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
        src/Base/Interfaces/IKeyboard.h
        src/Base/Interfaces/IMouse.h
        src/Base/Interfaces/IRender.h
        src/Base/Interfaces/ITransformable.h
        src/Rendering/Canvas/gl_canvas2d.cpp
        src/Rendering/Canvas/gl_canvas2d.h
        src/Managers/GlobalManager.cpp
        src/Managers/GlobalManager.h
        src/Vectors/Vector2.h
        src/Vectors/Vector3.h
        src/Vectors/Vector4.h
        src/Vectors/Matrix.h
        src/main.cpp
        src/Utilities.cpp
        src/Utilities.h
        src/Camera/Camera.cpp
        src/Camera/Camera.h
        src/Base3DObjects/Cube.cpp
        src/Base3DObjects/Cube.h
        src/Camera/CameraMovement.cpp
        src/Camera/CameraMovement.h
        src/Base3DObjects/Cylinder.cpp
        src/Base3DObjects/Cylinder.h
        src/Base/3D/Object3D.cpp
        src/Base/3D/Object3D.h
        src/Engine.cpp
        src/Engine.h
        src/Base/3D/Transform.cpp
        src/Base/3D/Transform.h
        src/Slider/HorizontalSlider.h
        src/Slider/HorizontalSlider.cpp
        src/Base/UI/ObjectUI.cpp
        src/Base/UI/ObjectUI.h
        src/Rendering/Renderer.cpp
        src/Rendering/Renderer.h
        src/Rendering/IShader.cpp
        src/Rendering/IShader.h
        src/Rendering/FlatShader/FlatShader.cpp
        src/Rendering/FlatShader/FlatShader.h
        src/Rendering/GoraudShader/GoraudShader.cpp
        src/Rendering/GoraudShader/GoraudShader.h
        src/Rendering/PhongShader/PhongShader.cpp
        src/Rendering/PhongShader/PhongShader.h
        src/Engine2D.cpp
        src/Engine2D.h
        src/Base/UI/Transform2D.cpp
        src/Base/UI/Transform2D.h src/BaseUIObjects/Rect.cpp src/BaseUIObjects/Rect.h src/Base3DObjects/OpenEndedCylinder.cpp src/Base3DObjects/OpenEndedCylinder.h src/Base3DObjects/ModelLoader.cpp src/Base3DObjects/ModelLoader.h src/Bitmap/Bitmap.cpp src/Bitmap/Bitmap.h src/FileLoader.cpp src/FileLoader.h)

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