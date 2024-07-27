cmake_minimum_required(VERSION 3.26)
project(RayTracerChaellenge)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_executable(main_run ${SOURCE_FILES})

include_directories(LinearAlgebra_lib)
add_subdirectory(LinearAlgebra_lib)

include_directories(Drawing_lib)
add_subdirectory(Drawing_lib)

target_link_libraries(main_run LinearAlgebra_lib Drawing_lib)

add_subdirectory(Google_tests)

