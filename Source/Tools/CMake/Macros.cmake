macro(ge_print_info)

message(STATUS "Platform name : ${CMAKE_SYSTEM_NAME}")
message(STATUS "Platform architecture : ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMake generator : ${CMAKE_GENERATOR}")
message(STATUS "CMake build type : ${CMAKE_BUILD_TYPE}")
message(STATUS "CMake configuration types : ${CMAKE_CONFIGURATION_TYPES}")

endmacro()

macro(ge_prepare_ouput_directory)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GE_OUPUT_DIRECTORY}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GE_OUPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GE_OUPUT_DIRECTORY}/lib)

endmacro()
