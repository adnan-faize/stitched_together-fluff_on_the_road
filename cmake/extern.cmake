# ========================================
# extern.cmake
# ========================================

set(STFR_OLD_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF)
set(STFR_OLD_CMAKE_POSITION_INDEPENDENT_CODE ${CMAKE_POSITION_INDEPENDENT_CODE})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# GLFW (Windows, Linux, MacOS)
if (STFR_PLATFORM_GLFW)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory(extern/glfw-3.4)
endif()

# GLAD (Windows, Linux)
if (STFR_RENDERER_OPENGL)
  add_library(glad STATIC extern/glad/src/glad.c)
  target_include_directories(glad PUBLIC extern/glad/include)
  set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

# GLM
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/glm-1.0.3)


# CR.H

if (CMAKE_BUILD_TYPE STREQUAL "Debug")



endif ()

# ENTT

add_subdirectory(extern/entt-3.16.0)

# GLAD



# GLFW





# IMGUI

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

  add_library(imgui STATIC
    extern/imgui-1.92.8/imgui.cpp
    extern/imgui-1.92.8/imgui_demo.cpp
    extern/imgui-1.92.8/imgui_draw.cpp
    extern/imgui-1.92.8/imgui_tables.cpp
    extern/imgui-1.92.8/imgui_widgets.cpp
    extern/imgui-1.92.8/backends/imgui_impl_glfw.cpp
    extern/imgui-1.92.8/backends/imgui_impl_opengl3.cpp
  )
  target_include_directories(imgui PUBLIC
    extern/imgui-1.92.8
    extern/imgui-1.92.8/backends
  )
  set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)
  target_link_libraries(imgui PRIVATE glad)

endif ()

# JOLT PHYSICS

set(TARGET_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(TARGET_HELLO_WORLD OFF CACHE BOOL "" FORCE)
set(TARGET_PERFORMANCE_TEST OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES OFF CACHE BOOL "" FORCE)
set(TARGET_VIEWER OFF CACHE BOOL "" FORCE)
set(JPH_USE_VK OFF CACHE BOOL "" FORCE)
set(JPH_USE_DX12 OFF CACHE BOOL "" FORCE)
set(JPH_USE_MTL OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/jolt-physics-5.6.0/Build)

set(BUILD_SHARED_LIBS ${STFR_OLD_BUILD_SHARED_LIBS})
set(CMAKE_POSITION_INDEPENDENT_CODE ${STFR_OLD_CMAKE_POSITION_INDEPENDENT_CODE})
