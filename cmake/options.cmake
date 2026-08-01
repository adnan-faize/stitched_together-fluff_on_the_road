# ========================================
# options.cmake
# ========================================

option(STFR_DEV_MODE "Build everything as separate DLLs for fast iteration" ON)

if (STFR_DEV_MODE)
  message(STATUS "STFR BUILD MODE : DEVELOPMENT (Shared DLLs)")
  set(BUILD_SHARED_LIBS ON)
  add_compile_definitions(STFR_SHARED_BUILD)
else ()
  message(STATUS "STFR BUILD MODE : RELEASE (Monolithic Static")
  set(BUILD_SHARED_LIBS OFF)
  add_compile_definitions(STFR_STATIC_BUILD)

  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif ()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
