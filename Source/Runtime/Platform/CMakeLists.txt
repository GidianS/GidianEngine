set(GE_PLATFORM_SOURCES
    Platform.cpp)

set(GE_PLATFORM_HEADERS
    Defines.hpp)

add_library(GEPlatform STATIC ${GE_PLATFORM_SOURCES} ${GE_PLATFORM_HEADERS})
