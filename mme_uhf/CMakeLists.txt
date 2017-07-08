cmake_minimum_required(VERSION 2.8)
project (mme_uhf)

add_definitions(-DBUILD_MODULE="MME_UHF")

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/uhf/include)
include_directories(${MDW_SOURCE_DIR}/mme/include)


file(GLOB_RECURSE  source_files src/*.cpp )

include_directories("src")
include_directories("src/dto")
include_directories("src/service")

add_library(mme_uhf SHARED ${source_files} )

target_link_libraries(mme_uhf toolbox)  
target_link_libraries(mme_uhf uhf)  
target_link_libraries(mme_uhf mme) 
 
