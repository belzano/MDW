cmake_minimum_required(VERSION 2.8)
project (uhf)

add_definitions(-DBUILD_MODULE="UHF")

include_directories("include")
include_directories(${MDW_SOURCE_DIR}/logger/include)
include_directories(${MDW_SOURCE_DIR}/toolbox/include)


file(GLOB_RECURSE source_files src/*)

include_directories("src/core")
include_directories("src/core/configuration")
include_directories("src/core/component")
include_directories("src/core/ability")
include_directories("src/core/property")
include_directories("src/core/command")
include_directories("src/core/managers")
include_directories("src/core/managers/events")
include_directories("src/core/managers/libloader")
include_directories("src/core/managers/threads")
include_directories("src/kvs/") 
include_directories("src/kvs/component") 
include_directories("src/http/") 
include_directories("src/http/component") 
include_directories("src/tasks/") 
include_directories("src/tasks/component") 
include_directories("src/logger/") 
include_directories("src/logger/component") 
include_directories("src/bootstrap/") 
include_directories("src/bootstrap/manager") 
include_directories("src/bootstrap/property") 
include_directories("src/bootstrap/configuration") 
include_directories("src")

add_library(uhf SHARED ${source_files})

target_link_libraries (uhf toolbox)
target_link_libraries (uhf logger)
target_link_libraries (uhf toolbox)
target_link_libraries (uhf ${Boost_LIBRARIES}) 
target_link_libraries (uhf ${Boost_FILESYSTEM_LIBRARY}) 
target_link_libraries (uhf ${OPENSSL_LIBRARIES}) 
target_link_libraries(uhf libdl.so)



