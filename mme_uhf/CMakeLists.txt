cmake_minimum_required(VERSION 2.8)
project (mme_uhf)

add_definitions(-DBUILD_MODULE="MME_UHF")

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/kvs/include)
include_directories(${MDW_SOURCE_DIR}/wtf_job/include)
include_directories(${MDW_SOURCE_DIR}/wtf_svc/include)
include_directories(${MDW_SOURCE_DIR}/mme/include)


file(GLOB_RECURSE  source_files *.cpp )
add_library(mme_uhf SHARED ${source_files} )

target_link_libraries(mme_uhf toolbox)  
target_link_libraries(mme_uhf kvs)  
target_link_libraries(mme_uhf wtf_svc) 
target_link_libraries(mme_uhf wtf_job)  
target_link_libraries(mme_uhf mme) 
 
