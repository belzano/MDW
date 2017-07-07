cmake_minimum_required(VERSION 2.8)
project (wtf_svc)

add_definitions(-DBUILD_MODULE="WTF")

 
include_directories("include")
include_directories(${MDW_SOURCE_DIR}/toolbox/include)

file(GLOB_RECURSE source_files src/* )
add_library(wtf_svc SHARED ${source_files})

target_link_libraries(wtf_svc toolbox)
target_link_libraries(wtf_svc libdl.so) 
