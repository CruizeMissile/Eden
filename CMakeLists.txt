cmake_minimum_required(VERSION 3.7)

project(eden)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/scaffold")
include(scaffold)

check_master_project(EDEN_MASTER_PROJECT)
option(EDEN_ENABLE_SAMPLES "Enable building of samples for eden" ${EDEN_MASTER_PROJECT})
option(EDEN_ENABLE_TESTS "Enable building of unit tests for eden" ${EDEN_MASTER_PROJECT})

add_subdirectory(eden)

if(EDEN_ENABLE_SAMPLES)
  add_subdirectory(samples)
endif()
