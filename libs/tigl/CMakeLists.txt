cmake_minimum_required(VERSION 3.16)


file(GLOB TIGL_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(tigl ${TIGL_SRC})