cmake_minimum_required(VERSION 2.8)
project (mme_wtf)

add_definitions(-DBUILD_MODULE="MME_WTF")

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/kvs/include)
include_directories(${MDW_SOURCE_DIR}/wtf_job/include)
include_directories(${MDW_SOURCE_DIR}/wtf_svc/include)
include_directories(${MDW_SOURCE_DIR}/mme/include)


file(GLOB_RECURSE  source_files *.cpp )
add_library(mme_wtf SHARED ${source_files} )

target_link_libraries(mme_wtf toolbox)  
target_link_libraries(mme_wtf kvs)  
target_link_libraries(mme_wtf wtf_svc) 
target_link_libraries(mme_wtf wtf_job)  
target_link_libraries(mme_wtf mme) 
 
