cmake_minimum_required(VERSION 3.16)

file(GLOB FPS_CAM_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(fpscam ${FPS_CAM_SRC})