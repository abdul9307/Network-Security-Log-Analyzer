# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ProjectFinal_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ProjectFinal_autogen.dir\\ParseCache.txt"
  "ProjectFinal_autogen"
  )
endif()
