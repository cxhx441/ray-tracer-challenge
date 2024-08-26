project(GraphicsLibrary)

set(HEADER_FILES
        Tuple.h
        Canvas.h
        Matrix.h
        Transformation.h
        Ray.h
        Sphere.h
        Intersection.h
        PointLight.h
        Material.h
        Lighting.h
        World.h
        Camera.h
        PreparedComputation.h
)

set(SOURCE_FILES
        Tuple.cpp
        Canvas.cpp
        Matrix.cpp
        Transformation.cpp
        Ray.cpp
        Sphere.cpp
        Intersection.cpp
        PointLight.cpp
        Material.cpp
        Lighting.cpp
        World.cpp
        Camera.cpp
        PreparedComputation.cpp
)

add_library(GraphicsLibrary_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})