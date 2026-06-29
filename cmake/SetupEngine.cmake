add_library(stfr_engine SHARED src/engine/engine_entrypoint.cpp)

target_include_directories(stfr_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
