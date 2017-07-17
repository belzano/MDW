cmake_minimum_required(VERSION 2.8)
project (mme_bin)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml  -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab")
add_definitions(-DBUILD_MODULE="TEST")


include_directories(${MDW_SOURCE_DIR}/mme/include)
include_directories(${MDW_SOURCE_DIR}/toolbox/include)
include_directories(${MDW_SOURCE_DIR}/uhf/include)

file(   GLOB_RECURSE
        source_files
        src/*
)

add_executable(mme_bin ${source_files})

target_link_libraries(mme_bin ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

target_link_libraries(mme_bin mme)
target_link_libraries(mme_bin toolbox)
target_link_libraries(mme_bin uhf)

