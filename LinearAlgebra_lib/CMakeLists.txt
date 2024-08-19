project(LinearAlgebra)

set(HEADER_FILES
        Tuple.h
        Canvas.h
        Matrix.h
        Transformation.h
        Ray.h
        Sphere.h
        Intersection.h
        Light.h
        Material.h
        Lighting.h
        World.h
)

set(SOURCE_FILES
        Tuple.cpp
        Canvas.cpp
        Matrix.cpp
        Transformation.cpp
        Ray.cpp
        Sphere.cpp
        Intersection.cpp
        Light.cpp
        Material.cpp
        Lighting.cpp
        World.cpp
)

add_library(LinearAlgebra_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})