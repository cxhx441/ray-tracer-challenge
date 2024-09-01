cmake_minimum_required(VERSION 3.26)

add_library(patterns STATIC
        CheckerPattern.cpp
        GradientPattern.cpp
        Pattern.cpp
        RingPattern.cpp
        StripedPattern.cpp
        RadialGradientPattern.cpp
        TestPattern.cpp
)
target_include_directories(patterns PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/GraphicsLibrary
)

target_link_libraries(patterns PUBLIC primitives)
