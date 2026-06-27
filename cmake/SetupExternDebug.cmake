if (CMAKE_BUILD_TYPE STREQUAL "Debug")

  # ==========================================================
  # CR.H
  # ==========================================================

  set(CR_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(CR_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory(extern/cr)

  # ==========================================================
  # ImGui
  # ==========================================================

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
