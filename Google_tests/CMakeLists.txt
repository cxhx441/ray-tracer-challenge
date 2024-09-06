cmake_minimum_required(VERSION 3.26)
project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run
        TupleTest.cpp
        CanvasTest.cpp
        MatrixTest.cpp
        TransformationTest.cpp
        RayTest.cpp
        SphereTest.cpp
        IntersectionTest.cpp
        LightTest.cpp
        MaterialTest.cpp
        LightingAnObjectTest.cpp
        WorldTest.cpp
        CameraTest.cpp
        ShapeTest.cpp
        PlaneTest.cpp
        PatternTest.cpp
        ColorTest.cpp
        CubeTest.cpp
        CylinderTest.cpp
        ConeTest.cpp
)

target_link_libraries(Google_Tests_run PRIVATE GraphicsLibrary_lib)

target_link_libraries(Google_Tests_run PRIVATE gtest gtest_main)

target_include_directories(Google_Tests_run PRIVATE ${CMAKE_SOURCE_DIR}/GraphicsLibrary)