# ========================================
# devenv.cmake
# ========================================

if (CMAKE_EXPORT_COMPILE_COMMANDS)
  # Remove any existing file/link to prevent conflicts
  file(REMOVE "${CMAKE_SOURCE_DIR}/compile_commands.json")

  # Attempt to create a symlink
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_SOURCE_DIR}/compile_commands.json"
    RESULT_VARIABLE SYMLINK_RESULT
    ERROR_QUIET
  )

  # Check if the symlink succeeded
  if ("${SYMLINK_RESULT}" STREQUAL "0")
    message(STATUS "Symlink created for compile_commands.json.")
  else()
    message(
      STATUS
      "Symlinks blocked. "
      "Falling back to build-time copy for compile_commands.json."
    )
    # Copy compile_commands.json to the root of the project
    add_custom_target(
      UpdateCompileCommands ALL
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json"
      COMMENT "Copying compile_commands.json to project root for Clangd"
      VERBATIM
    )
  endif()
endif()

# Compiler diagnostics & color
if (MSVC)
  add_compile_options(
    /W4          # High warning level
    /WX          # Treat warnings as errors (Remove if too strict)
    /permissive- # Enforce strict C++ standard conformance
  )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(
    -fdiagnostics-color=always
    -Wall        # Standard warnings
    -Wextra      # Extra warnings
    -Wpedantic   # Warn if code violates strict ISO ++ standards
    -Werror      # Treat all warnings as errors
  )
endif()
