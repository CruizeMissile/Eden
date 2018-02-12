
function(handle_build_problems)

if (${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
  message("----------------------------------------------------------")
  message("In source build are not supported. It is recommended that you")
  message("use a build/ subdirectory:")
  message("   $ cmake . <OPTIONS> -Bbuild")
  message("")
  message("Make sure that you clean up the smake artifacts with:")
  message("   $ rm -rf CMakeFiles CMakeCache.txt")
  message("----------------------------------------------------------")
  message("")
  message(FATAL_ERROR "Stopping build.")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
  message("There is no BUILD_TYPE selected. Please choose a build type.")
  message("Defaulting to Release.")
  set(CMAKE_BUILD_TYPE "Release")
endif()

endfunction()
handle_build_problems()
