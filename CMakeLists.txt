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
                          LIB_GAME_ENTRYPOINT="libstfr_engine.so"
                          LIB_ENGINE_ENTRYPOINT=""
  )
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(SetupExtern)
include(SetupExternDebug)

include(SetupEngine)
include(SetupEngineDebug)

include(SetupGame)

include(SetupCore)

# ==========================================================
# Generate hashes header for integrity checks in main.cpp
# ==========================================================

set(INTEGRITY_HEADER "${CMAKE_CURRENT_BINARY_DIR}/generated/dll_hashes.h")

find_package(Python3 REQUIRED COMPONENTS Interpreter)

add_custom_command(
  OUTPUT "${INTEGRITY_HEADER}"
  COMMAND ${Python3_EXECUTABLE} "${CMAKE_SOURCE_DIR}/scripts/generate_hashes.py"
    "${INTEGRITY_HEADER}"
    "stfr_engine=$<TARGET_FILE:stfr_engine>"
  DEPENDS stfr_engine
  COMMENT "Hashing engine DLLs for integrity check..."
)

add_custom_target(generate_hash_header DEPENDS "${INTEGRITY_HEADER}")

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

add_dependencies(STFR generate_hash_header)
target_include_directories(STFR PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
target_link_libraries(STFR PRIVATE stfr_core stfr_engine)
