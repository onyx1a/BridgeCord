cmake_minimum_required(VERSION 3.24)
project(DiscordBridge)

find_package(Python 3.7 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(discord_gamesdk_cmake)

pybind11_add_module(DiscordBridge src/main.cpp)

target_link_libraries(DiscordBridge PUBLIC discord)
set_target_properties(DiscordBridge PROPERTIES CXX_VISIBILITY_PRESET "hidden")