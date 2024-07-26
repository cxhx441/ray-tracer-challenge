project(LinearAlgebra)

set(HEADER_FILES
        LinearAlgebra.h
        )

set(SOURCE_FILES
        LinearAlgebra.cpp
)

add_library(LinearAlgebra_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})