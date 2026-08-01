# ========================================
# ToolPackAssets.cmake
# ========================================

set(RAW_ASSETS_DIR "${CMAKE_SOURCE_DIR}/res")
set(PACKED_ASSETS_FILE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets.pak")

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  # In Release, pack assets into a .pak file automatically during build
  add_custom_command(
    OUTPUT "${PACKED_ASSETS_FILE}"
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_SOURCE_DIR}/tools/pack_assets.py" "${RAW_ASSETS_DIR}" "${PACKED_ASSETS_FILE}"
    DEPENDS "${CMAKE_SOURCE_DIR}/tools/pack_assets.py"
    COMMENT "Packing assets into ${PACKED_ASSETS_FILE}..."
  )

  add_custom_target(pack_assets ALL DEPENDS "${PACKED_ASSETS_FILE}")
  
  # Tell the C++ code to use the packed assets and where to find them
  add_compile_definitions(STFR_USE_PACKED_ASSETS)
  add_compile_definitions(STFR_ASSET_PATH="assets.pak")
else()
  # In Debug, load raw files from the source 'res' directory directly
  add_compile_definitions(STFR_ASSET_PATH="${RAW_ASSETS_DIR}/")
endif()
