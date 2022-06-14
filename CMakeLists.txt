cmake_minimum_required(VERSION 3.16)
project(3dGraphics)

set(CMAKE_CXX_STANDARD 20)

include_directories("libs/glfw/include")
include_directories("libs/glad/include")
include_directories("libs/tigl/include")
include_directories("libs/stb_image/include")
include_directories("libs/glm")

add_subdirectory(libs/glm)
add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/tigl)
add_subdirectory(libs/stb_image)

include_directories("modules/fpscam/include")
include_directories("modules/model_loader/include")
include_directories("modules/ecs/include")

add_subdirectory(modules/fpscam)
add_subdirectory(modules/model_loader)
add_subdirectory(modules/ecs)


add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} fpscam)
target_link_libraries(${CMAKE_PROJECT_NAME} model_loader)
target_link_libraries(${CMAKE_PROJECT_NAME} ecs)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glm)
target_link_libraries(${CMAKE_PROJECT_NAME} glad)
target_link_libraries(${CMAKE_PROJECT_NAME} tigl)
target_link_libraries(${CMAKE_PROJECT_NAME} stb_image)

