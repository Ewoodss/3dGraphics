cmake_minimum_required(VERSION 3.16)

file(GLOB GLAD_SRC
        "src/*.c"
        "include/*.h"
        )

add_library(glad ${GLAD_SRC})