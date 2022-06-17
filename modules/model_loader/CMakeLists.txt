cmake_minimum_required(VERSION 3.16)

file(GLOB MODEL_LOADER_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(model_loader ${MODEL_LOADER_SRC})

target_link_libraries(model_loader ecs)