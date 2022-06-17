cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)
set(TEST_NAME tests)

# These tests can use the Catch2-provided main
add_executable(${TEST_NAME} test.cpp)


target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST_NAME} PRIVATE input_system)
