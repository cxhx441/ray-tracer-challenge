cmake_minimum_required(VERSION 3.26)
project(RayTracerChaellenge)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(RayTracerChallenge_run ${SOURCE_FILES})

include_directories(LinearAlgebra_lib)
add_subdirectory(LinearAlgebra_lib)

target_link_libraries(RayTracerChallenge_run LinearAlgebra_lib)

add_subdirectory(Google_tests)

