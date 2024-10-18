# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/testapp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/testapp_autogen.dir/ParseCache.txt"
  "testapp_autogen"
  )
endif()
