cmake_minimum_required(VERSION 3.24)
project(DiscordBridge)

add_subdirectory(discord_gamesdk_cmake)

add_executable(DiscordBridge src/main.cpp)

target_link_libraries(DiscordBridge discord)