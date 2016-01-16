cmake_minimum_required(VERSION 2.8)
project (logger)

add_definitions(-DBUILD_MODULE="LOGGER")

include_directories("include")
include_directories(${Boost_INCLUDE_DIRS}) 

file(GLOB_RECURSE source_files src/*)

add_library(logger SHARED ${source_files})

target_link_libraries(logger ${Boost_LIBRARIES})
