if (POLICY CMP0054)

cmake_policy(SET CMP0054 NEW)

endif()

if (POLICY CMP0072)

cmake_policy(SET CMP0072 NEW)

endif()

if (POLICY CMP0076)

cmake_policy(SET CMP0076 NEW)

endif()

if (POLICY CMP0078)

cmake_policy(SET CMP0078 NEW)

endif()

include(GNUInstallDirs)

include(${GE_PORJECT_SOURCE_TOOLS_DIR}/CMake/Options.cmake)
include(${GE_PORJECT_SOURCE_TOOLS_DIR}/CMake/Macros.cmake)

set(GE_PROJECT_BUILD_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(GE_PROJECT_OUPUT_DIRECTORY ${GE_PROJECT_BUILD_DIRECTORY}/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})

set(GE_PROJECT_SOURCES)
set(GE_PROJECT_HEADERS)

if (NOT CMAKE_BUILD_TYPE)

message(WARNING "No build type specified, defaulting to 'Debug'. To change this, use -DCMAKE_BUILD_TYPE=<type>.")

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

endif()

if (NOT CMAKE_CONFIGURATION_TYPES)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "Reset the configuration types to what you need." FORCE)

endif()

ge_print_info()
