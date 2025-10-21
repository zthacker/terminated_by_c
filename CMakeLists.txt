cmake_minimum_required(VERSION 4.0)
project(terminated_by_c C)

set(CMAKE_C_STANDARD 17)

# Set output directory based on build type
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)

# SDL3 Setup - checks environment variable first, falls back to external directory
if(DEFINED ENV{SDL3_DIR})
    set(SDL3_DIR $ENV{SDL3_DIR})
    message(STATUS "Using SDL3 from environment: ${SDL3_DIR}")
else()
    set(SDL3_DIR "${CMAKE_SOURCE_DIR}/external/SDL")
    message(STATUS "Using SDL3 from project: ${SDL3_DIR}")
endif()

# Set SDL3 paths for MinGW
set(SDL3_INCLUDE_DIR "${SDL3_DIR}/x86_64-w64-mingw32/include")
set(SDL3_LIB_DIR "${SDL3_DIR}/x86_64-w64-mingw32/lib")
set(SDL3_BIN_DIR "${SDL3_DIR}/x86_64-w64-mingw32/bin")

# Check if SDL3 exists
if(NOT EXISTS "${SDL3_INCLUDE_DIR}/SDL3/SDL.h")
    message(FATAL_ERROR "SDL3 not found! Expected: ${SDL3_INCLUDE_DIR}/SDL3/SDL.h")
endif()

# Include SDL3 headers (MinGW structure)
include_directories(${SDL3_INCLUDE_DIR})

# Link SDL3 libraries (MinGW structure, 64-bit)
link_directories(${SDL3_LIB_DIR})

# Gather source files
file(GLOB_RECURSE SOURCE "src/*.c")

# Add cJSON from external
set(CJSON_SOURCE ${CMAKE_SOURCE_DIR}/external/cJSON/cJSON.c)

add_executable(terminated_by_c main.c ${SOURCE} ${CJSON_SOURCE})

# Include directories
target_include_directories(terminated_by_c PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/cJSON)

# Link SDL3
target_link_libraries(terminated_by_c SDL3)

# Copy SDL3.dll to output directory
add_custom_command(
        TARGET terminated_by_c POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_BIN_DIR}/SDL3.dll"
        "$<TARGET_FILE_DIR:terminated_by_c>/SDL3.dll"
        COMMENT "Copying SDL3.dll to build directory"
)

# Copy character data
add_custom_command(
        TARGET terminated_by_c POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/gamedata/character.json"
        "$<TARGET_FILE_DIR:terminated_by_c>/character.json"
        COMMENT "Copying character data to build dir"
)