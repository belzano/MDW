# The name of our project is "MDW". CMakeLists files in this project can 
# refer to the root source directory of the project as ${MDW_SOURCE_DIR} and 
# to the root binary directory of the project as ${MDW_BINARY_DIR}. 

cmake_minimum_required(VERSION 2.8)
project (MDW)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMDW_FILENAME='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# Boost packages required
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON) 
find_package(Boost 1.42.0 COMPONENTS regex) 
find_package(Boost 1.42.0 COMPONENTS date_time)
find_package(Boost 1.42.0 COMPONENTS filesystem) 
find_package(Boost 1.42.0 COMPONENTS interprocess)
find_package(Boost REQUIRED COMPONENTS thread )


message("Boost include dir: ${Boost_INCLUDE_DIR} ; libraries: ${Boost_LIBRARIES}")

set (MDW_VERSION_MAJOR 0)
set (MDW_VERSION_MINOR 1)
set (MDW_VERSION_BUILD 0)

# ----------------------------------------------------------------------------
# Process subdirectories
# ----------------------------------------------------------------------------

# dependencies
add_subdirectory (gtest)

# core modules
add_subdirectory (toolbox)
add_subdirectory (logger)

# uhf
add_subdirectory (uhf)
add_subdirectory (uhf_be)
# helpers modules for uhf
add_subdirectory (uhf_sysmon)
add_subdirectory (uhf_mhd)
#add_subdirectory (pistache)

add_subdirectory (mme)
add_subdirectory (mme_bin)
add_subdirectory (mme_uhf)
