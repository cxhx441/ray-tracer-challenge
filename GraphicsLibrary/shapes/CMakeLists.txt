cmake_minimum_required(VERSION 3.26)

add_library(shapes STATIC
        Material.cpp
        Plane.cpp
        Shape.cpp
        Sphere.cpp
)
target_include_directories(shapes PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/GraphicsLibrary
)

target_link_libraries(shapes PUBLIC primitives patterns)
