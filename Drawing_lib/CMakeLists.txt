project(Drawing)

set(HEADER_FILES
        Canvas.h
        )

set(SOURCE_FILES
        Canvas.cpp
)

add_library(Drawing_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})