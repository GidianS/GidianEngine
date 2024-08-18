set(GE_LAUNCHER_SOURCES)
set(GE_LAUNCHER_HEADERS)

if (LINUX)

list(APPEND GE_LAUNCHER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Linux/Main.cpp)

endif()

add_executable(GELauncher ${GE_LAUNCHER_SOURCES})

target_link_libraries(GELauncher GECore GEPlatform)
