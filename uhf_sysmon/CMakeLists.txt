cmake_minimum_required(VERSION 2.8)
project (uhfsysmon)

add_definitions(-DBUILD_MODULE="UHF_SYSMON")


set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.42.0 COMPONENTS regex) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()


include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/uhf/include)

file(GLOB_RECURSE  source_files src/*.cpp)
include_directories("src")

add_library(uhfsysmon SHARED ${source_files} )

target_link_libraries(uhfsysmon uhf)  
target_link_libraries(uhfsysmon toolbox)  
target_link_libraries(uhfsysmon ${Boost_LIBRARIES}) 


