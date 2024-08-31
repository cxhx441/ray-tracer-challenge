cmake_minimum_required(VERSION 3.26)

add_library(primitives STATIC
        Intersection.cpp
        Matrix.cpp
        Ray.cpp
        Transformation.cpp
        Tuple.cpp
)

#target_include_directories(primitives PUBLIC ${PROJECT_SOURCE_DIR}/GraphicsLibrary)