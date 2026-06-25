

# ==========================================================
# GLFW
# ==========================================================

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/glfw)

# ==========================================================
# GLAD
# ==========================================================

add_library(glad extern/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/include)

# ==========================================================
# GLM
# ==========================================================

add_subdirectory(extern/glm)

# ==========================================================
# OpenGL
# ==========================================================

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
