cmake_minimum_required(VERSION 3.18)

# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})

project(RogEng)

file(GLOB_RECURSE RogEngSrc Source/*.c)

add_library(RogEng STATIC ${RogEngSrc})

target_link_libraries(RogEng glfw)
target_link_libraries(RogEng OpenGL::GL)
