cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE ECS_SRC CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.h"
        )

add_library(ecs ${ECS_SRC})

target_link_libraries(ecs model_loader)
target_link_libraries(ecs input_system)
target_link_libraries(ecs game_timer)