cmake_minimum_required(VERSION 2.8)
project (uhf_be)

add_definitions(-DBUILD_MODULE="UHF BE")

include_directories(${MDW_SOURCE_DIR}/toolbox/include) 
include_directories(${MDW_SOURCE_DIR}/uhf/include) 

file(GLOB_RECURSE source_files src/*)

add_executable(uhf_be ${source_files})

target_link_libraries (uhf_be uhf)
target_link_libraries (uhf_be toolbox)
target_link_libraries (uhf_be ${Boost_LIBRARIES}) 
target_link_libraries (uhf_be ${Boost_FILESYSTEM_LIBRARY}) 
target_link_libraries (uhf_be ${OPENSSL_LIBRARIES}) 
target_link_libraries (uhf_be ${CMAKE_THREAD_LIBS_INIT})
