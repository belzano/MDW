cmake_minimum_required(VERSION 2.8)
project (mme_bin)

add_definitions(-DBUILD_MODULE="TEST")

include_directories(${MDW_SOURCE_DIR}/mme/include)
include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/uhf/include)

file(   GLOB_RECURSE
        source_files
        src/*
)

add_executable(mme_bin ${source_files})

target_link_libraries(mme_bin mme) 
target_link_libraries(mme_bin toolbox)
target_link_libraries(mme_bin uhf)

target_link_libraries(mme_bin ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(mme_bin libopencv_core.so )
target_link_libraries(mme_bin libopencv_features2d.so )
target_link_libraries(mme_bin libopencv_imgproc.so )

