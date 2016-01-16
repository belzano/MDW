cmake_minimum_required(VERSION 2.8)
project (uhfcommand)

add_definitions(-DBUILD_MODULE="CMD")

include_directories("include")
include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(${MDW_SOURCE_DIR}/logger/include/)
include_directories(${MDW_SOURCE_DIR}/toolbox/include/)

file(GLOB_RECURSE source_files "src/*pp" )
file(GLOB_RECURSE header_files "include/command/*pp")

set (include_dir "")
foreach (_header_file ${header_files})
    get_filename_component(_dir ${_header_file} PATH)
    list (APPEND include_dir ${_dir})
endforeach()
list(REMOVE_DUPLICATES include_dir)

add_library(uhfcommand SHARED ${source_files} )

target_link_libraries(uhfcommand logger) 
target_link_libraries(uhfcommand toolbox) 
target_link_libraries(uhfcommand ${Boost_LIBRARIES}) 
