project(LinearAlgebra)

set(HEADER_FILES
        Tuple.h
        Canvas.h
        )

set(SOURCE_FILES
        Tuple.cpp
        Canvas.cpp
)

add_library(LinearAlgebra_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})