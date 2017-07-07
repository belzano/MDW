cmake_minimum_required(VERSION 2.8)
project (wtf_job)


add_definitions(-DBUILD_MODULE="JOB")

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/kvs/include)

file(GLOB_RECURSE source_files "src/*pp" )
file(GLOB_RECURSE header_files "include/job/*pp")

set (include_dir "")
foreach (_header_file ${header_files})
    get_filename_component(_dir ${_header_file} PATH)
    list (APPEND include_dir ${_dir})
endforeach()
list(REMOVE_DUPLICATES include_dir)

include_directories("include")


add_library(wtf_job SHARED ${source_files} )

target_link_libraries (wtf_job kvs) 
target_link_libraries (wtf_job toolbox) 

