cmake_minimum_required(VERSION 4.0)
project(terminated_by_c C)

set(CMAKE_C_STANDARD 17)

# bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin/RelWithDebInfo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin/MinSizeRel)


file(GLOB_RECURSE SOURCE "src/*.c"
    #grab the cJSON.c also
    ${CMAKE_SOURCE_DIR}/include/utils/cJSON.c)

add_executable(terminated_by_c main.c ${SOURCE}
        include/data/loader.h
        include/utils/file_path.h)

# include dir
target_include_directories(terminated_by_c PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

# post build
add_custom_command(
        TARGET terminated_by_c POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/gamedata/character.json"
            "$<TARGET_FILE_DIR:terminated_by_c>/character.json"
        COMMENT "Copying character data to build dir"
)