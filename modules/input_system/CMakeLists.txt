cmake_minimum_required(VERSION 3.16)

file(GLOB INPUT_SYSTEM_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(input_system ${INPUT_SYSTEM_SRC})