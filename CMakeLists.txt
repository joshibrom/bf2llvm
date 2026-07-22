cmake_minimum_required(VERSION 3.21)

project(bf2llvm LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)


# Source collection

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS
    ${SRC_DIR}/*.cpp
)

# Remove Main.cpp from library sources
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*Main\\.cpp$")

file(GLOB_RECURSE ALL_PATHS
    LIST_DIRECTORIES true
    CONFIGURE_DEPENDS
    ${SRC_DIR}/*
)

set(INCLUDE_DIRS ${SRC_DIR})

foreach(path ${ALL_PATHS})
    if(IS_DIRECTORY ${path})
        list(APPEND INCLUDE_DIRS ${path})
    endif()
endforeach()

list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Main executable

add_executable(bf2llvm
    ${SRC_DIR}/Main.cpp
)

target_sources(bf2llvm PRIVATE ${SOURCE_FILES})

# Warnings + Sanitizers

if(UNIX AND NOT APPLE)

    target_compile_options(bf2llvm PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -fsanitize=address
        -fsanitize=undefined
    )

    target_link_options(bf2llvm PUBLIC
        -fsanitize=address
        -fsanitize=undefined
    )

endif()
