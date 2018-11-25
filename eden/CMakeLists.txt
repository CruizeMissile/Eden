
# currently only working on opengl. more renderers in the future
option(EDEN_BUILD_OPENGL "Enable building opengl renderer" ON)
option(EDEN_BUILD_VULKAN "Enable building vulkan renderer" OFF)

if (WIN32)
  option(EDEN_BUILD_DX11 "Enable building directx 11 renderer" OFF)
  option(EDEN_BUILD_DX12 "Enable building directx 12 renderer" OFF)
endif()

##############################################################################################
# List of files

macro(create_file_list list_name)
  foreach(f ${ARGN})
    file(GLOB cpp_list "${f}/*.cpp")
    file(GLOB hpp_list "${f}/*.hpp")
    file(GLOB inl_list "${f}/*.inl")
    list(APPEND ${list_name} ${cpp_list})
    list(APPEND ${list_name} ${hpp_list})
    list(APPEND ${list_name} ${inl_list})
  endforeach(f ${ARGN})
endmacro()

create_file_list(files_app "${CMAKE_CURRENT_LIST_DIR}/app")
create_file_list(files_core "${CMAKE_CURRENT_LIST_DIR}/core")
create_file_list(files_ecs "${CMAKE_CURRENT_LIST_DIR}/ecs")
create_file_list(files_input "${CMAKE_CURRENT_LIST_DIR}/input")

# agnostic files
create_file_list(files_ag_renderer "${CMAKE_CURRENT_LIST_DIR}/renderer" "${CMAKE_CURRENT_LIST_DIR}/renderer/platform")

# platform files
create_file_list(files_win32_renderer "${CMAKE_CURRENT_LIST_DIR}/renderer/platform/win32")

# renderers
create_file_list(files_gl "${CMAKE_CURRENT_LIST_DIR}/renderer/api/gl")

##############################################################################################
# Final list of files

list(APPEND files_final_win32
  ${files_win32_renderer}
)

list(APPEND files_final_eden
  ${files_app}
  ${files_core}
  ${files_ecs}
  ${files_input}
  ${files_ag_renderer}
)

if(WIN32)
  list(APPEND files_final_eden ${files_final_win32})
endif()

##############################################################################################
# Target creation

# Creating the core engine lib
sf_create_library(eden
  SOURCE_LIST ${files_final_eden}
  CXX_VERSION 17
  INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${GLFW_INCLUDE_DIR}
  DEPENDS ${GLFW_LIBRARY} ${PRIDE_LIB}
)
sf_target_set_folder(${EDEN_LIB} "eden")

if (EDEN_BUILD_OPENGL AND NOT ${files_gl} STREQUAL "")
  find_package(OpenGL)
  set(EDEN_GL eden_gl)
  if (OpenGL_FOUND)
    add_library(${EDEN_GL} STATIC ${files_gl})
    set_target_properties(${EDEN_GL} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${EDEN_GL} PUBLIC ${OPENGL_INCLUDE_DIR})
    target_include_directories(${EDEN_GL} PUBLIC "${PROJECT_SOURCE_DIR}/external/OpenGL/include")
    target_link_libraries(${EDEN_GL} eden, ${OPENGL_LIBRARY})
    sf_target_source_group(${EDEN_GL} DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/renderer/renderer")
    sf_target_set_folder(${EDEN_GL} "eden/renderer")
    sf_target_cxx(${EDEN_GL} 17)
  else()
    message(STATUS "MIssing OpenGL ${EDEN_GL} renderer will not be added to the project")
  endif()
endif()



# list(APPEND eden_files
#   "${CMAKE_CURRENT_LIST_DIR}/app/app.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/app/app.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/app/event.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/app/event.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/app/input.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/app/input.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/app/window.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/app/window.cpp"

#   "${CMAKE_CURRENT_LIST_DIR}/ecs/archetype.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/archetype.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/defines.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/director.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/director.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/director.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/dispatcher.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/dispatcher.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/dispatcher.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/entity.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/entity.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/entity.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/id.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/iterator.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/iterator.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/property.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/property.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/store.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/store.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/system.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/system.cpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/view.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/view.inl"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs/utils.hpp"
#   "${CMAKE_CURRENT_LIST_DIR}/ecs.hpp"
# )

# sf_create_library(eden
#   SOURCE_LIST ${eden_files}
#   CXX_VERSION 17
#   INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${GLFW_INCLUDE_DIR}
#   DEPENDS ${GLFW_LIBRARY} ${PRIDE_LIB}
# )
