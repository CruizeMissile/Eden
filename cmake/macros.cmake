macro(add_subdirectory_ex arg)
    add_subdirectory(${arg})
endmacro()

macro(detect_platform)
    message(STATUS "-------------------------------")
    message(STATUS "Detecting Platform")
    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif()

    # if(NOT LINUX) should work, too, if you need that
    if(LINUX)
        message(STATUS "OS >>> Linux")
        # linux stuff here
    elseif(WIN32)
        message(STATUS "OS >>> Windows")
        # stuff that should happen not on Linux
    endif()

    message(STATUS "COMPILER >>> ${CMAKE_CXX_COMPILER_ID}")

    message(STATUS "BUILD_SHARED_LIBS >>> ${BUILD_SHARED_LIBS}")

    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
        add_definitions(-D_SCL_SECURE_NO_WARNINGS=1)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj /W3")
    endif()

endmacro()


macro(print_info)
    message(STATUS "-------------------------------")
    message(STATUS "PROJECT_BINARY_DIR >>> ${PROJECT_BINARY_DIR}")
    message(STATUS "CMAKE_CXX_FLAGS >>> ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS_DEBUG >>> ${CMAKE_CXX_FLAGS_DEBUG}")
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE >>> ${CMAKE_CXX_FLAGS_RELEASE}")
    message(STATUS "-------------------------------")
endmacro()

macro(set_output_paths)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
endmacro()

macro(set_project_custom_defines)
    add_definitions(-DENGINE_DIRECTORY="${PROJECT_SOURCE_DIR}" -DSHADER_INCLUDE_DIRECTORY="${BGFX_DIR}/src")
endmacro()
