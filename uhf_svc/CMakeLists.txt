cmake_minimum_required(VERSION 2.8)
project (uhfsvc)

add_definitions(-DBUILD_MODULE="SVC")

 
include_directories("include")
include_directories(${MDW_SOURCE_DIR}/uhf/include/)
include_directories(${MDW_SOURCE_DIR}/logger/include/)
include_directories(${MDW_SOURCE_DIR}/toolbox/include/)
include_directories(${MDW_SOURCE_DIR}/uhf_tasks/include/)
#include_directories(${MDW_SOURCE_DIR}/uhf/include/)

file(GLOB_RECURSE source_files src/* )
add_library(uhfsvc SHARED ${source_files})

target_link_libraries(uhfsvc logger)
target_link_libraries(uhfsvc toolbox)
target_link_libraries(uhfsvc uhf)
target_link_libraries(uhfsvc uhftask)
#target_link_libraries(uhfsvc uhf)
#target_link_libraries(uhfsvc libdl.so) 
