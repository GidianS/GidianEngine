set(GE_CORE_SOURCES
    Types/Generic.cpp)

set(GE_CORE_HEADERS
    Types/Integer.hpp)

add_library(GECore STATIC ${GE_CORE_SOURCES} ${GE_CORE_HEADERS})
