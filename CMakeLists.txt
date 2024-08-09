cmake_minimum_required(VERSION 3.28)
project(RayTracerChallenge CUDA)

set(CMAKE_CUDA_STANDARD 17)
#set(CMAKE_CUDA_FLAGS "-Wall")

set(SOURCE_FILES main.cu)
add_executable(main_run ${SOURCE_FILES})

include_directories(LinearAlgebra_lib)
add_subdirectory(LinearAlgebra_lib)

target_link_libraries(main_run LinearAlgebra_lib)

add_subdirectory(Google_tests)

set_target_properties(main_run PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
