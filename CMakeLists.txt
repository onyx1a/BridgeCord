cmake_minimum_required(VERSION 3.24)
project(bridgecord)

find_package(Python 3.7 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(discord_gamesdk_cmake)

pybind11_add_module(${CMAKE_PROJECT_NAME} src/main.cpp src/Instance.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC discord)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET "hidden")