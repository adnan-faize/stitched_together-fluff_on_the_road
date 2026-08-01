# ========================================
# stfr_renderer.cmake
# ========================================

set(RENDERER_SOURCES src/renderer/renderer.hpp)

if (STFR_RENDERER_OPENGL)
  file(
    GLOB_RECURSE GL_SOURCES CONFIGURE_DEPENDS
    "src/renderer/opengl/*.cpp"
    "src/renderer/opengl/*.hpp"
  )
  list(APPEND RENDERER_SOURCES ${GL_SOURCES})
elseif (STFR_RENDERER_METAL)
  file(
    GLOB_RECURSE METAL_SOURCES CONFIGURE_DEPENDS
    "src/renderer/metal/*.cpp"
    "src/renderer/metal/*.hpp"
  )
  list(APPEND RENDERER_SOURCES ${METAL_SOURCES})
endif()

add_library(stfr_renderer ${RENDERER_SOURCES})

set_target_properties(stfr_renderer PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(stfr_renderer PRIVATE STFR_RENDERER_BUILD)

target_link_libraries(stfr_renderer PUBLIC stfr_core glm)

if (STFR_RENDERER_OPENGL)
  target_link_libraries(stfr_renderer PRIVATE glad)
endif ()
