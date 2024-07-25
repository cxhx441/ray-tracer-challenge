project(LinearAlgebra)

set(HEADER_FILES
        Point3.h
        Vec3.h
        )

set(SOURCE_FILES
        Point3.cpp
        Vec3.cpp
)

add_library(LinearAlgebra_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})