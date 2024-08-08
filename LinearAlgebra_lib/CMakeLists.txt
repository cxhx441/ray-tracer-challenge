project(LinearAlgebra)

set(HEADER_FILES
        Tuple.h
        Canvas.h
        Matrix.h
        Transformation.h
        Ray.h
        Sphere.h
        Intersection.h
)

set(SOURCE_FILES
        Tuple.cpp
        Canvas.cpp
        Matrix.cpp
        Transformation.cpp
        Ray.cpp
        Sphere.cpp
        Intersection.cpp
)

add_library(LinearAlgebra_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})