cmake_minimum_required(VERSION 2.8)
project (kvs)

add_definitions(-DBUILD_MODULE="KVS")

include_directories("include")
include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(${MDW_SOURCE_DIR}/toolbox/include)

file(GLOB_RECURSE source_files "src/*pp" )
file(GLOB_RECURSE header_files "include/toolbox/*pp")

set (include_dir "")
foreach (_header_file ${header_files})
    get_filename_component(_dir ${_header_file} PATH)
    list (APPEND include_dir ${_dir})
endforeach()
list(REMOVE_DUPLICATES include_dir)


add_library(kvs SHARED ${source_files} )

target_link_libraries (kvs toolbox) 
target_link_libraries (kvs ${Boost_LIBRARIES}) 
target_link_libraries (kvs ${OPENSSL_LIBRARIES}) 



