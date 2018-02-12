
cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(filter_group)
include(flags)

project(eden)
include(build_problems)

# Checking if we are the master project or have been submoduled as a dependency
set(MASTER_PROJECT OFF)
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  set(MASTER_PROJECT ON)
endif()

option(EDEN_ENABLE_SAMPLES "Enable to build the samples" ${MASTER_PROJECT})
option(EDEN_ENABLE_TESTS "Enable to build the unit tests" ${MASTER_PROJECT})

add_subdirectory(3rdparty)
add_subdirectory(eden)

if (EDEN_ENABLE_SAMPLES)
  add_subdirectory(samples)
endif()

if (EDEN_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
