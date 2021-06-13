cmake_minimum_required(VERSION 3.18)

project(Sandbox)

file(GLOB_RECURSE SandSrc Source/*.c)

include_directories(${CMAKE_SOURCE_DIR}/Engine/Source/)

add_executable(Sandbox ${SandSrc})

target_link_libraries(Sandbox RogEng)
