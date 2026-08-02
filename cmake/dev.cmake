# ========================================
# dev.cmake
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
  if (SYMLINK_RESULT EQUAL 0)
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
