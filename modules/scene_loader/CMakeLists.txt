cmake_minimum_required(VERSION 3.16)

file(GLOB SCENE_LOADER_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(scene_loader ${SCENE_LOADER_SRC})

target_link_libraries(scene_loader json)
target_link_libraries(scene_loader ecs)