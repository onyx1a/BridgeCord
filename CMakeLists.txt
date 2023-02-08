cmake_minimum_required(VERSION 3.24)
project(DiscordBridge)

find_package(Python 3.7 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(discord_gamesdk_cmake)

add_library(API STATIC src/Instance.cpp)
set_target_properties(API PROPERTIES POSITION_INDEPENDENT_CODE ON)

pybind11_add_module(${CMAKE_PROJECT_NAME} src/main.cpp)
#add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/Instance.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC discord PUBLIC API)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET "hidden")