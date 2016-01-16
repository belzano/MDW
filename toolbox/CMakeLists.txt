cmake_minimum_required(VERSION 2.8)
project (toolbox)

add_definitions(-DBUILD_MODULE="TBX")

include_directories("include")
include_directories(${Boost_INCLUDE_DIRS}) 

file(GLOB_RECURSE source_files "src/*pp" )
file(GLOB_RECURSE header_files "include/toolbox/*pp")

set (include_dir "")
foreach (_header_file ${header_files})
    get_filename_component(_dir ${_header_file} PATH)
    list (APPEND include_dir ${_dir})
endforeach()
list(REMOVE_DUPLICATES include_dir)


add_library(toolbox SHARED ${source_files} )

target_link_libraries(toolbox ${Boost_LIBRARIES}) 
target_link_libraries(toolbox ${OPENSSL_LIBRARIES}) 


# build the test binary
include_directories(${gtest_SOURCE_DIR}/include)
file(GLOB_RECURSE test_files test/* )
add_executable(test_toolbox ${test_files})
target_link_libraries(test_toolbox gtest)
target_link_libraries(test_toolbox toolbox)

