# SPDX-License-Identifier: GPL-2.0-or-later
#
# Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
#

cmake_minimum_required(VERSION 3.9)
project(bfjson VERSION "1.0" LANGUAGES C)

include(GNUInstallDirs)
include(CheckIncludeFiles)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(BFJSON_HEADER_PATH ${PROJECT_SOURCE_DIR}/include)
set(BFJSON_GENERATED_PATH ${PROJECT_BINARY_DIR}/generated)

option(ENABLE_EXAMPLES "Build examples" OFF)
if(ENABLE_EXAMPLES)
    enable_testing()
    add_subdirectory(examples)
endif()

configure_file(
    ${CMAKE_MODULE_PATH}/config.h.in
    ${PROJECT_BINARY_DIR}/generated/bfjson/config.h
)

FILE(GLOB_RECURSE SRC_HEADER "include/*.h")
FILE(GLOB_RECURSE SRC_SOURCE "src/*.c")
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/generated)

set(BFJSON_LIBRARY
    ${SRC_HEADER}
    ${SRC_SOURCE}
)

add_library(bfjson_object SHARED ${BFJSON_LIBRARY})
add_library(bfjson_static STATIC ${BFJSON_LIBRARY})
add_library(bfjson_shared SHARED ${BFJSON_LIBRARY})
add_library(bfjson ALIAS bfjson_object)

target_link_libraries(bfjson_object bfdev)
target_link_libraries(bfjson_static bfdev)
target_link_libraries(bfjson_shared bfdev)

if(${CMAKE_PROJECT_NAME} STREQUAL "bfjson")
    install(DIRECTORY
        ${BFJSON_HEADER_PATH}/bfjson
        ${BFJSON_GENERATED_PATH}/bfjson
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(TARGETS
        bfjson_static bfjson_shared
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()
