cmake_minimum_required(VERSION 3.10)
project(CrossCompilation C)

# Configurações gerais
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# Modo Debug vs Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Flags específicas de Release
set(CMAKE_C_FLAGS_RELEASE "-O2 -s")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Platform detection
if(WIN32)
    message(STATUS "Platform: Windows")
    add_definitions(-D_WINDOWS)
    if(MINGW)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
    endif()
elseif(UNIX)
    message(STATUS "Platform: Linux/Unix")
    add_definitions(-D_UNIX)
    if(APPLE)
        message(STATUS "Platform: macOS")
    endif()
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(COMMON_SOURCES
    src/platform.c
)

set(MAIN_SOURCES
    src/main.c
    ${COMMON_SOURCES}
)

set(TEST_SOURCES
    src/test.c
    ${COMMON_SOURCES}
)

# Main executable
add_executable(program ${MAIN_SOURCES})

# Test executable
add_executable(test ${TEST_SOURCES})

# Enable testing
enable_testing()
add_test(NAME basic_tests COMMAND test)

# Installation
install(TARGETS program
    RUNTIME DESTINATION bin
)

# Summary
message(STATUS "═══════════════════════════════════════")
message(STATUS "Cross-Compilation Project (CMake)")
message(STATUS "═══════════════════════════════════════")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C Flags: ${CMAKE_C_FLAGS}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "═══════════════════════════════════════")
message(STATUS "Build with: cmake --build build")
message(STATUS "Test with: ctest -C build")
