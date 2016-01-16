cmake_minimum_required(VERSION 2.8)
project (wtftasks)

add_definitions(-DWTF_MODULE="TASKS")

 
include_directories("include")
include_directories(${WTF_SOURCE_DIR}/toolbox/include/)
include_directories(${WTF_SOURCE_DIR}/api/include/)

file(GLOB_RECURSE source_files src/* )
add_library(wtftasks SHARED ${source_files})

target_link_libraries(wtftasks wtftoolbox)
target_link_libraries(wtftasks wtfapi)
