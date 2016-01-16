cmake_minimum_required(VERSION 2.8)
project (uhf_bin)

add_definitions(-DBUILD_MODULE="BIN")

include_directories(${MDW_SOURCE_DIR}/toolbox/include) 
include_directories(${MDW_SOURCE_DIR}/uhf/include) 
include_directories(${MDW_SOURCE_DIR}/uhf_core/include) 

file(GLOB_RECURSE source_files src/*)

add_executable(uhf_be ${source_files})

target_link_libraries (uhf_be uhfcore)
target_link_libraries(uhf_be ${CMAKE_THREAD_LIBS_INIT})
