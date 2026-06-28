cmake_minimum_required(VERSION 3.30)
project(STFR C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_definitions(GAME_TITLE="Stitched Together : Fluff on the Road"
                        GAME_VERSION=""
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(STFR_DEBUG
                          LIB_GAME_ENTRYPOINT=""
                          LIB_ENGINE_ENTRYPOINT=""
  )
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(SetupExtern)
include(SetupExternDebug)

include(SetupEngine)
include(SetupEngineDebug)
include(SetupGame)

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
