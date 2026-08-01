# ========================================
# os.cmake
# ========================================

message(STATUS "Detecting Target Operating System...")

if     (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "Target OS : Windows (GLFW + OpenGL 4.3)")
  add_compile_definitions(
    STFR_OS_WINDOWS
    STFR_PLATFORM_GLFW
    STFR_RENDERER_OPENGL
  )
  set(STFR_OS_WINDOWS ON)
  set(STFR_PLATFORM_GLFW ON)
  set(STFR_RENDERER_OPENGL ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(STATUS "Target OS : Linux (GLFW + OpenGL 4.3)")
  add_compile_definitions(
    STFR_OS_LINUX
    STFR_PLATFORM_GLFW
    STFR_RENDERER_OPENGL
  )
  set(STFR_OS_LINUX ON)
  set(STFR_PLATFORM_GLFW ON)
  set(STFR_RENDERER_OPENGL ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "MacOS")
  message(STATUS "Target OS : MacOS (GLFW + Metal)")
  add_compile_definitions(
    STFR_OS_MACOS
    STFR_PLATFORM_GLFW
    STFR_RENDERER_METAL
  )
  set(STFR_OS_MACOS ON)
  set(STFR_PLATFORM_GLFW ON)
  set(STFR_RENDERER_METAL ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "PS4")
  message(STATUS "Target OS : PS4 (OpenOrbis)")
  add_compile_definitions(
    STFR_OS_PS4
    STFR_PLATFORM_PS4
  )
  set(STFR_OS_PS4 ON)
  set(STFR_PLATFORM_PS4 ON)
else   ()
  message(
    FATAL_ERROR
    "STFR Build Failed : Unknown or Unsupported Operating System!"
  )
endif  ()
