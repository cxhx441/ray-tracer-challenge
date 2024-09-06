cmake_minimum_required(VERSION 3.26)

add_library(shapes STATIC
        Material.cpp
        Plane.cpp
        Shape.cpp
        Sphere.cpp
        TestShape.cpp
        HollowGlassSphere.cpp
        Cube.cpp
        HollowGlassCube.cpp
        Cylinder.cpp
        Cylinder.h
        HollowGlassCylinder.cpp
        HollowGlassCylinder.h
)
target_include_directories(shapes PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/GraphicsLibrary
)

target_link_libraries(shapes PUBLIC primitives patterns)
