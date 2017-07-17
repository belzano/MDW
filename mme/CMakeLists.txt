cmake_minimum_required(VERSION 2.8)
project (mme)

add_definitions(-DBUILD_MODULE="MME")
#set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/uhf/include)
include_directories(${MDW_SOURCE_DIR}/mme/include)

add_subdirectory( src )

include_directories(src/bom)
include_directories(src/shapes)
include_directories(src/process)


file(GLOB_RECURSE api_source_files "src/*pp" )
file(GLOB_RECURSE api_header_files "include/*pp")

set (api_include_dir "")
foreach (_header_file ${api_header_files})
    get_filename_component(_dir ${_header_file} PATH)
    list (APPEND api_include_dir ${_dir})
endforeach()
list(REMOVE_DUPLICATES api_include_dir)

include_directories(${api_include_dir})


add_library(mme SHARED ${api_source_files} )


target_link_libraries( mme toolbox)
target_link_libraries( mme uhf)

target_link_libraries( mme libopencv_core.so )
target_link_libraries( mme libopencv_features2d.so )
target_link_libraries( mme libopencv_imgproc.so )
target_link_libraries( mme libopencv_highgui.so )

# Only available for opencv > 3.0
#target_link_libraries( mme libopencv_imgcodecs.so )

