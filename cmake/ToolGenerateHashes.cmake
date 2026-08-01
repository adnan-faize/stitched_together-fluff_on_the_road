# ========================================
# ToolGenerateHashes.cmake
# ========================================

set(INTEGRITY_HEADER "${CMAKE_CURRENT_BINARY_DIR}/generated/hashes.h")

add_custom_command(
  OUTPUT "${INTEGRITY_HEADER}"
  COMMAND ${Python3_EXECUTABLE} "${CMAKE_SOURCE_DIR}/tools/generate_hashes.py"
    "${INTEGRITY_HEADER}"
    "stfr_engine=$<TARGET_FILE:stfr_engine>"
  DEPENDS stfr_engine
  COMMENT "Hashing shared libraries for integrity checks..."
)

add_custom_target(generate_hash_header DEPENDS "${INTEGRITY_HEADER}")
