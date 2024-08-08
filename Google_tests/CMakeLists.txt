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
)

target_link_libraries(Google_Tests_run LinearAlgebra_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)