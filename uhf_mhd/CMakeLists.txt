cmake_minimum_required(VERSION 2.8)
project (uhfmhd)

add_definitions(-DBUILD_MODULE="UHFMHD")

include(${CMAKE_CURRENT_SOURCE_DIR}/findMHD.cmake)
 
include_directories("include")
include_directories(${MDW_SOURCE_DIR}/logger/include/)
include_directories(${MDW_SOURCE_DIR}/toolbox/include/)
include_directories(${MDW_SOURCE_DIR}/uhf/include/)

file(GLOB_RECURSE source_files src/* )
include_directories("src")
include_directories("src/component")
include_directories("src/manager")

add_library(uhfmhd SHARED ${source_files})

target_link_libraries(uhfmhd logger)
target_link_libraries(uhfmhd toolbox)
target_link_libraries(uhfmhd uhf)
target_link_libraries(uhfmhd ${MHD_LIBRARY})
