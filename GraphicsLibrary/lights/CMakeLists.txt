cmake_minimum_required(VERSION 3.26)

add_library(lights STATIC
        PointLight.cpp
)
target_include_directories(lights PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/GraphicsLibrary
)

target_link_libraries(lights PUBLIC primitives)
