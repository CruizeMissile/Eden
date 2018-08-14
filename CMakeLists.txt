cmake_minimum_required(VERSION 3.8)

project(eden)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/scaffold")
include(scaffold)

sf_check_master_project(EDEN_MASTER_PROJECT)
option(ENABLE_SAMPLES "Enable building of samples for eden" ${EDEN_MASTER_PROJECT})
option(ENABLE_TESTS "Enable building of unit tests for eden" ${EDEN_MASTER_PROJECT})

option(ENABLE_CLANG_FORMAT "Enable formatting with clang-format" OFF)
option(ENABLE_CLANG_TIDY "Enable static analisys with cppcheck" OFF)
option(ENABLE_CPPCHECK "Enable static analisys with cppcheck" OFF)
option(ENABLE_CODECOV "Enable code coverage reports with codecov" OFF)

add_subdirectory(external)
add_subdirectory(eden)

if(ENABLE_SAMPLES AND EDEN_MASTER_PROJECT)
  add_subdirectory(samples)
endif()

if(ENABLE_TESTS AND EDEN_MASTER_PROJECT AND NOT NO_TESTS)
  add_subdirectory(tests)
endif()

sf_setup_modules()

if(ENABLE_CLANG_FORMAT AND EDEN_MASTER_PROJECT)
  include(clangformat)
  sf_clangformat_add_target(${EDEN_LIB})
  sf_clangformat_create_command()
endif()

if(ENABLE_CLANG_TIDY AND EDEN_MASTER_PROJECT)
  include(clangtidy)
  sf_clangtidy_add_target(${EDEN_LIB})
  sf_clangtidy_create_command()
endif()

if(ENABLE_CPPCHECK AND EDEN_MASTER_PROJECT)
  include(cppcheck)
  sf_cppcheck_add_target(${EDEN_LIB})
  sf_cppcheck_create_command(CHECKS warning,performance)
endif()
