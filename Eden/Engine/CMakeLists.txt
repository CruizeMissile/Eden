# setting the current directory as the root path of eden
set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

# searching all source files recursivly and adding it to the list of source files
file(GLOB_RECURSE _source_list
	LIST_DIRECTORIES false
	"${_src_root_path}/*.cpp"
	"${_src_root_path}/*.h"
)

# adding the precompiled header and list of source files to the library eden
add_library(eden Precompiled.h Precompiled.cpp ${_source_list})

# making sure that cmake knows that Precompiled is the precompiled header file
add_precompiled_header(eden Precompiled.h SOURCE_CXX Precompiled.cpp FORCEINCLUDE)

# looping though all source files and adding them to a source group. this will make sure
# that when generating with msvc that the solution explorer looks like the source directory
foreach(_source IN ITEMS ${_source_list})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

# Make sure the compiler can find include files for our library when
# other libraries or exectuables link to it
target_include_directories(eden PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Dependencies
##

# glfw
target_include_directories(eden PUBLIC ${GLFW_INCLUDE_DIR})
target_link_libraries(eden PUBLIC ${GLFW_LIBRARY})

# cml
target_include_directories(eden PUBLIC ${CML_INCLUDE_DIR})
