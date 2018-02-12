# setting the current directory as the root path of eden
set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

# searching all source files recursivly and adding it to the list of source files
file(GLOB_RECURSE _source_list
	LIST_DIRECTORIES false
	"${_src_root_path}/*.cpp"
	"${_src_root_path}/*.h"
)

add_executable(eden-tests ${_source_list})
target_link_libraries(eden-tests catch eden)
target_include_directories(eden-tests PUBLIC ${CATCH_INCLUDE_DIR} ${_src_root_path})
add_filter_group("${_source_list}" "${CMAKE_CURRENT_SOURCE_DIR}")
