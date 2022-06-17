cmake_minimum_required(VERSION 3.16)
project(3dGraphics)

set(CMAKE_CXX_STANDARD 20)

include_directories("libs/glfw/include")
include_directories("libs/glad/include")
include_directories("libs/tigl/include")
include_directories("libs/stb_image/include")
include_directories("libs/json/include")
include_directories("libs/glm")

add_subdirectory(libs/glm)
add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/tigl)
add_subdirectory(libs/stb_image)
add_subdirectory(libs/json)


include_directories("modules/model_loader/include")
include_directories("modules/ecs/include")
include_directories("modules/input_system/include")
include_directories("modules/game_timer/include")
include_directories("modules/scene_loader/include")

add_subdirectory(modules/model_loader)
add_subdirectory(modules/ecs)
add_subdirectory(modules/input_system)
add_subdirectory(modules/game_timer)
add_subdirectory(modules/scene_loader)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} model_loader)
target_link_libraries(${CMAKE_PROJECT_NAME} ecs)
target_link_libraries(${CMAKE_PROJECT_NAME} input_system)
target_link_libraries(${CMAKE_PROJECT_NAME} game_timer)
target_link_libraries(${CMAKE_PROJECT_NAME} scene_loader)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glm)
target_link_libraries(${CMAKE_PROJECT_NAME} glad)
target_link_libraries(${CMAKE_PROJECT_NAME} tigl)
target_link_libraries(${CMAKE_PROJECT_NAME} stb_image)

if (MSVC)

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ../build)
else ()
    add_subdirectory(test)
endif ()