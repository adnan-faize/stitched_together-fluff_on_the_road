# ========================================
# CMakeLists.txt
# ========================================

cmake_minimum_required(VERSION 3.30)
project(STFR VERSION 0.1.0 LANGUAGES C CXX)

# ========================================
# GLOBAL SETTINGS & OPTIONS
# ========================================

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(options)
include(os)

# ========================================
# THIRD-PARTY LIBRARIES
# ========================================

include(extern)

# ========================================
# ENGINE MODULES
# ========================================

include(modules/stfr_core)
include(modules/stfr_platform)
include(modules/stfr_renderer)

# ========================================
# GAME & APP
# ========================================

include(modules/stfr)

# ========================================
# DEV UTILS
# ========================================

include(devenv)
