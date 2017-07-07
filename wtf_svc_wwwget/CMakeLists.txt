cmake_minimum_required(VERSION 2.8)
project (wtf_svc_wwwget)

add_definitions(-DBUILD_MODULE="WTF_SVC_WWWGET")

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/wtf_svc/include)

file(GLOB_RECURSE source_files *.cpp)

add_library(wtf_svc_wwwget SHARED ${source_files} )
 
target_link_libraries(wtf_svc_wwwget toolbox)
target_link_libraries(wtf_svc_wwwget wtf_svc) 


