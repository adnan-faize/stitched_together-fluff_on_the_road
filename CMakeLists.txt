cmake_minimum_required(VERSION 3.30)
project(STFR C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(GAME_TITLE="Stitched Together : Fluff on the Road")

# ==========================================================
# Core Dependencies (GLFW, GLAD, GLM)
# ==========================================================
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/glfw)

add_library(glad extern/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/include)

add_subdirectory(extern/glm)

find_package(OpenGL REQUIRED)

# ==========================================================
# Jolt Physics
# ==========================================================
set(CMAKE_DISABLE_FIND_PACKAGE_Vulkan ON)
set(TARGET_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(TARGET_HELLO_WORLD OFF CACHE BOOL "" FORCE)
set(TARGET_PERFORMANCE_TEST OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES OFF CACHE BOOL "" FORCE)
set(TARGET_VIEWER OFF CACHE BOOL "" FORCE)
set(USE_SSE4_2 ON CACHE BOOL "" FORCE)
add_subdirectory(extern/jolt/Build)

# ==========================================================
# Debug ONLY (cr.h & imgui)
# ==========================================================
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(STFR_DEBUG)

  # --- cr.h
  set(CR_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(CR_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory(extern/cr)

  # --- imgui
  add_library(imgui STATIC
    extern/imgui/imgui.cpp
    extern/imgui/imgui_demo.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
  )
  target_include_directories(imgui PUBLIC extern/imgui extern/imgui/backends)
  target_include_directories(imgui PRIVATE extern/glfw/include)
endif()

# ==========================================================
# Engine
# ==========================================================

# TODO

# ==========================================================
# Game
# ==========================================================

# TODO

# ==========================================================
# Executable target
# ==========================================================
add_executable(STFR src/main.cpp)

target_link_libraries(STFR PRIVATE
  glad
  glfw
  glm
  OpenGL::GL
  Jolt
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(STFR PRIVATE cr imgui)
endif()
