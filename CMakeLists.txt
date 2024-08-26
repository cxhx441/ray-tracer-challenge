cmake_minimum_required(VERSION 3.26)
project(RayTracerChallenge)

set(CMAKE_CXX_STANDARD 17)

IF(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
ENDIF()

set(SOURCE_FILES main.cpp)

add_executable(main_run ${SOURCE_FILES})

include_directories(GraphicsLibrary)
add_subdirectory(GraphicsLibrary)

target_link_libraries(main_run GraphicsLibrary_lib)

add_subdirectory(Google_tests)

