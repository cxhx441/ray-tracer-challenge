cmake_minimum_required(VERSION 3.26)

add_library(scene STATIC
        Camera.cpp
        LightingModels.cpp
        PreparedComputation.cpp
        World.cpp
)
target_include_directories(scene PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/GraphicsLibrary
)

target_link_libraries(scene PUBLIC primitives shapes lights)
