cmake_minimum_required(VERSION 2.8)
project (wtf_svc_sysmon)

add_definitions(-DBUILD_MODULE="SYSMON")


set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.42.0 COMPONENTS regex) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()


include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/wtf_svc/include)

file(   GLOB_RECURSE
        source_files
        *.cpp
)

add_library(wtf_svc_sysmon SHARED ${source_files} )

target_link_libraries(wtf_svc_sysmon wtf_svc)  
target_link_libraries(wtf_svc_sysmon toolbox)  
target_link_libraries(wtf_svc_sysmon ${Boost_LIBRARIES}) 


