cmake_minimum_required(VERSION 2.8)
project (wtf_daemon)

add_definitions(-DBUILD_MODULE="DMN")

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/mme/include)
include_directories(${MDW_SOURCE_DIR}/kvs/include)
include_directories(${MDW_SOURCE_DIR}/wtf_job/include)

file(   GLOB_RECURSE source_files src/* )

add_executable(wtf_daemon ${source_files} )

target_link_libraries (wtf_daemon ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries (wtf_daemon toolbox) 
target_link_libraries (wtf_daemon mme) 
target_link_libraries (wtf_daemon kvs) 
target_link_libraries (wtf_daemon wtf_job)


