cmake_minimum_required(VERSION 2.8)
project (uhf)

add_definitions(-DBUILD_MODULE="UHF")

include_directories("include")
include_directories(${MDW_SOURCE_DIR}/logger/include)
include_directories(${MDW_SOURCE_DIR}/toolbox/include)

file(GLOB_RECURSE source_files src/*)

include_directories("src/")

add_library(uhf SHARED ${source_files})

target_link_libraries (uhf toolbox)
