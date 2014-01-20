cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project("SDL2 OpenGL Samples")


include_directories("./external/glew-1.10.0/include")
include_directories("./external/glut-3.7.6")
include_directories("./external/SDL2-2.0.1/include")

# TODO: Make crossplatform and clean directories 
link_directories("../external/glew-1.10.0/lib/Release/Win32")
link_directories("../external/glut-3.7.6")
link_directories("../external/SDL2-2.0.1/lib/x86")

add_executable("SDL2 OpenGL 3D Shapes" Shapes3D.cpp)

target_link_libraries("SDL2 OpenGL 3D Shapes" SDL2.lib SDL2main.lib glew32.lib glut32.lib)