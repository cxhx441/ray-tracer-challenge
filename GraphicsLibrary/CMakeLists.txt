cmake_minimum_required(VERSION 3.26)

add_subdirectory(display)
add_subdirectory(lights)
add_subdirectory(patterns)
add_subdirectory(primitives)
add_subdirectory(scene)
add_subdirectory(shapes)

add_library(GraphicsLibrary_lib INTERFACE)

target_link_libraries(GraphicsLibrary_lib INTERFACE
        display
        lights
        patterns
        primitives
        scene
        shapes
)