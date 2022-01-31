# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Spend-Note-Client_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Spend-Note-Client_autogen.dir/ParseCache.txt"
  "Spend-Note-Client_autogen"
  )
endif()
