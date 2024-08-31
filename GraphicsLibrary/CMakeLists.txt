cmake_minimum_required(VERSION 3.26)

set(HEADER_FILES
        Canvas.h
        PointLight.h
        Lighting.h
        scene/World.h
        scene/Camera.h
        scene/PreparedComputation.h
)

set(SOURCE_FILES
        Canvas.cpp
        PointLight.cpp
        Lighting.cpp
        scene/World.cpp
        scene/Camera.cpp
        scene/PreparedComputation.cpp
)

add_subdirectory(primitives)
add_subdirectory(patterns)
add_subdirectory(shapes)

add_library(GraphicsLibrary_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(GraphicsLibrary_lib PUBLIC
        primitives
        patterns
        shapes
)