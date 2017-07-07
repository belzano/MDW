cmake_minimum_required(VERSION 2.8)
project (wtf_be)

add_definitions(-DBUILD_MODULE="WTF")

 
include_directories(${MDW_SOURCE_DIR}/wtf_svc/include)
include_directories(${MDW_SOURCE_DIR}/toolbox/include)

file(GLOB_RECURSE source_files src/*)
add_executable(wtf_be ${source_files})


target_link_libraries (wtf_be wtf_svc)
target_link_libraries (wtf_be toolbox)
 
target_link_libraries(wtf_be libmicrohttpd.so)
target_link_libraries(wtf_be libdl.so) 
