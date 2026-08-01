# ========================================
# stfr.cmake
# ========================================

add_executable(stfr_app src/main.cpp)

target_link_libraries(stfr_app PRIVATE
  stfr_platform
  stfr_renderer
  stfr_core
)

set_target_properties(stfr_app PROPERTIES
  INSTALL_RPATH "$ORIGIN"
  BUILD_WITH_INSTALL_RPATH TRUE
  OUTPUT_NAME "STFR"
)
