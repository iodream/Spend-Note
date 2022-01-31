# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "libdal/CMakeFiles/libdal_autogen.dir/AutogenUsed.txt"
  "libdal/CMakeFiles/libdal_autogen.dir/ParseCache.txt"
  "libdal/libdal_autogen"
  )
endif()
