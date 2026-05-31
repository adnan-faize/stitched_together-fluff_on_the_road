cmake_minimum_required(VERSION 3.30)
project(STFR C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(GAME_TITLE="Stitched Together : Fluff on the Road")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/glfw)

add_library(glad extern/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/include)

find_package(OpenGL REQUIRED)

add_executable(STFR src/main.cpp)
target_link_libraries(STFR PRIVATE glad glfw OpenGL::GL)
target_include_directories(glm PRIVATE extern/glm)
