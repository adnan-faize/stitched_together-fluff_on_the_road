# ========================================
# stfr_core.cmake
# ========================================

file(
  GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
  "src/core/*.cpp"
  "src/core/*.hpp"
  "src/shared/*.hpp"
)

add_library(stfr_core ${CORE_SOURCES})

target_include_directories(stfr_core PUBLIC src)

target_compile_definitions(stfr_core PRIVATE STFR_CORE_BUILD)
