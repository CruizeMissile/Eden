#
# Glfw
#
set(GLFW_BUILD_EXAMPLES FALSE CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS FALSE CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS FALSE CACHE BOOL "" FORCE)
set(GLFW_INSTALL FALSE CACHE BOOL "" FORCE)
set(GLFW_LIBRARY "glfw" PARENT_SCOPE)
get_filename_component(GLFW_DIR "./glfw/" ABSOLUTE)
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include PARENT_SCOPE)
add_subdirectory(glfw)
sf_target_set_folder("glfw" external)

#
# Pride
#
add_subdirectory(pride)
sf_target_set_folder(pride eden/external)

#
# LLGL

add_subdirectory(llgl)
sf_target_set_folder(LLGL eden/external/llgl)

macro(llgl_external_folder target)
  if ($target)
    sf_target_set_folder($target eden/external/llgl)
  endif()
endmacro()

llgl_external_folder(LLGL)
llgl_external_folder(LLGL_Direct3D11)
llgl_external_folder(LLGL_Direct3D12)
llgl_external_folder(LLGL_Vulkan)

