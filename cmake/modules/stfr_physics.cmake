# ========================================
# stfr_physics.cmake
# ========================================

add_library(stfr_physics STATIC)

target_sources(stfr_physics PRIVATE

)

target_link_libraries(stfr_physics PUBLIC stfr_core Jolt)

target_include_directories(stfr_physics PUBLIC src/physics)
