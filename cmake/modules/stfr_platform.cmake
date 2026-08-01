# ========================================
# stfr_pltform.cmake
# ========================================

set(PLATFORM_SOURCES src/platform/platform.hpp)

if (STFR_PLATFORM_GLFW)
  file(
    GLOB_RECURSE GLFW_SOURCES CONFIGURE_DEPENDS
    "src/platform/glfw/*.cpp"
    "src/platform/glfw/*.hpp"
  )
  list(APPEND PLATFORM_SOURCES ${GLFW_SOURCES})
elseif (STFR_PLATFORM_PS4)
  file(
    GLOB_RECURSE PS4_SOURCES CONFIGURE_DEPENDS
    "src/platform/ps4/*.cpp"
    "src/platform/ps4/*.hpp"
  )
  list(APPEND PLATFORM_SOURCES ${PS4_SOURCES})
endif ()

add_library(stfr_platform ${PLATFORM_SOURCES})

set_target_properties(stfr_platform PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(stfr_platform PRIVATE STFR_PLATFORM_BUILD)

target_link_libraries(stfr_platform PUBLIC stfr_core)

if (STFR_PLATFORM_GLFW)
  target_link_libraries(stfr_platform PRIVATE glfw)
endif()

if (APPLE)
  target_link_libraries(
    stfr_platform PRIVATE "-framework Cocoa" "-framework Metal"
  )
endif ()
