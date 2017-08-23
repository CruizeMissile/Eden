
cmake_minimum_required(VERSION 3.1.3)

project(eden)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(macros)
include(enable_sanitizers)
include(precompiled_header)

option(BUILD_SHARED_LIBS
    "Build package with shared libraries."
    OFF
)

# list(APPEND SANITIZERS "custom")
enable_sanitizers("${SANITIZERS}")
detect_platform()
print_info()
set_output_paths()

add_subdirectory_ex(3rdparty)
add_subdirectory_ex(Eden)

# Building samples
if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    add_subdirectory_ex(samples)
endif()

set_project_custom_defines()
