cmake_minimum_required(VERSION 3.28)

project(rewind_engine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build tests" ON)

include(cmake/warnings.cmake)

add_subdirectory(external)

add_subdirectory(libs/common)
add_subdirectory(libs/sim)
add_subdirectory(libs/net)
add_subdirectory(libs/replay)
add_subdirectory(libs/demo_game)

add_subdirectory(apps/server)
add_subdirectory(apps/client)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
