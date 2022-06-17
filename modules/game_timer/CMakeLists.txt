cmake_minimum_required(VERSION 3.16)

file(GLOB GAME_TIMER_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(game_timer ${GAME_TIMER_SRC})