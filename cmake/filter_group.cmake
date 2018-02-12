
macro(add_filter_group source_list root_dir)
  foreach(source ${source_list})
    get_filename_component(parent_dir ${source} DIRECTORY)
    file(RELATIVE_PATH group "${root_dir}" "${parent_dir}")
    string(REPLACE "/" "\\" group "${group}")
    source_group("${group}" FILES "${source}")
  endforeach()
endmacro()
