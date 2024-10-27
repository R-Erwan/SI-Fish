cmake_minimum_required(VERSION 3.10)
project(SI_FISH)

set(CMAKE_CXX_STANDARD 11)

# Ajouter les dépendances installées sous WSL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)
find_package(JPEG REQUIRED)

add_executable(CubeGL cube.cpp
        PrimitiveSphere.cpp
        PrimitiveSphere.h
        PrimitiveTorus.cpp
        PrimitiveTorus.h
        Point.cpp
        Point.h
        PrimitiveCylindre.cpp
        PrimitiveCylindre.h
        PrimitiveTrunquedPyramid.cpp
        PrimitiveTrunquedPyramid.h
)

include_directories(${JPEG_INCLUDE_DIRS})

# Lier les bibliothèques OpenGL et FreeGLUT
target_link_libraries(CubeGL OpenGL::GL GLUT::GLUT GLU ${JPEG_LIBRARIES})
