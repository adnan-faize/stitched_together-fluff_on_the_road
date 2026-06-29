file(GLOB CORE_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.hpp"
)

add_library(stfr_core ${CORE_SOURCES})

target_include_directories(stfr_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/core")
