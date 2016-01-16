cmake_minimum_required(VERSION 2.8)
project (uhfhttp)

add_definitions(-DBUILD_MODULE="HTTP")
 
include_directories("include")
include_directories(${MDW_SOURCE_DIR}/logger/include/)
include_directories(${MDW_SOURCE_DIR}/toolbox/include/)
#include_directories(${MDW_SOURCE_DIR}/uhf/include/)
include_directories(${MDW_SOURCE_DIR}/uhf_svc/include/)

file(GLOB_RECURSE source_files src/* )
add_library(uhfhttp SHARED ${source_files})

target_link_libraries(uhfhttp logger)
target_link_libraries(uhfhttp toolbox)
#target_link_libraries(uhfhttp uhf)
target_link_libraries(uhfhttp uhfsvc)
