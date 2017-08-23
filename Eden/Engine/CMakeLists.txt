file(GLOB_RECURSE libsrc *.h *.hpp *.cpp *.c *.cc)

add_library(eden Precompiled.h Precompiled.cpp)
add_precompiled_header(eden Precompiled.h SOURCE_CXX Precompiled.cpp FORCEINCLUDE)

add_subdirectory_ex(Application)
add_subdirectory_ex(Core)
add_subdirectory_ex(Ecs)
add_subdirectory_ex(Math)

# Make sure the compiler can find include files for our library when
# other libraries or exectuables link to it
target_include_directories(eden PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# glfw
target_include_directories(eden PUBLIC ${GLFW_INCLUDE_DIR})
target_link_libraries(eden PUBLIC ${GLFW_LIBRARY})

# cml
target_include_directories(eden PUBLIC ${CML_INCLUDE_DIR})
