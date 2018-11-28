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

add_subdirectory(llgl)
sf_target_set_folder(LLGL            eden/external/llgl)
sf_target_set_folder(LLGL_Direct3D11 eden/external/llgl)
sf_target_set_folder(LLGL_OpenGL     eden/external/llgl)
