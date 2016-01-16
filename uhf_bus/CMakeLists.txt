cmake_minimum_required(VERSION 2.8)
project (wtfbus)

add_definitions(-DWTF_MODULE="BUS")

 
include_directories("include")
include_directories(${WTF_SOURCE_DIR}/toolbox/include/)
include_directories(${WTF_SOURCE_DIR}/api/include/)
include_directories(${WTF_SOURCE_DIR}/tasks/include/)

file(GLOB_RECURSE source_files src/* )
add_library(wtfbus SHARED ${source_files})

target_link_libraries(wtfbus wtftoolbox)
target_link_libraries(wtfbus wtfapi)
target_link_libraries(wtfbus wtftasks)
