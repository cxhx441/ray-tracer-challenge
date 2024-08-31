cmake_minimum_required(VERSION 3.26)

add_library(display STATIC
        Canvas.cpp
)
target_include_directories(display PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/GraphicsLibrary
)

target_link_libraries(display PUBLIC primitives scene)
